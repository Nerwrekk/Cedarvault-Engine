#include "MeanScript/MeanScript.h"

#include "MeanScript/host/nethost.h"
#include "MeanScript/host/coreclr_delegates.h"
#include "MeanScript/host/hostfxr.h"

#include "MeanScript/MeanScriptBindings.h"
#include "MeanScript/Primitives/MeanString.h"

// Standard headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#ifdef WIN32
	#include <Windows.h>

	#define STR(s) L##s
	#define CH(c) L##c
	#define DIR_SEPARATOR L'\\'

	#define string_compare wcscmp

#else
	#include <dlfcn.h>
	#include <limits.h>
	#include <sys/ptrace.h>
	#include <unistd.h>

	#define STR(s) s
	#define CH(c) c
	#define DIR_SEPARATOR '/'
	#define MAX_PATH PATH_MAX

	#define string_compare strcmp

#endif

using string_t = std::basic_string<char_t>;

/********************************************************************************************
 * Function used to load and activate .NET Core
 ********************************************************************************************/
#ifdef WIN32
	#define MEAN_STR(str) L##str
#else
	#define MEAN_STR(str) str
#endif

namespace
{
	// Globals to hold hostfxr exports
	hostfxr_initialize_for_dotnet_command_line_fn init_for_cmd_line_fptr;
	hostfxr_initialize_for_runtime_config_fn init_for_config_fptr;
	hostfxr_get_runtime_delegate_fn get_delegate_fptr;
	hostfxr_run_app_fn run_app_fptr;
	hostfxr_close_fn close_fptr;

	// Forward declarations
	void* load_library(const char_t*);
	void* get_export(void*, const char*);

#ifdef WIN32
	void* load_library(const char_t* path)
	{
		HMODULE h = ::LoadLibraryW(path);
		assert(h != nullptr);
		return (void*)h;
	}
	void* get_export(void* h, const char* name)
	{
		void* f = ::GetProcAddress((HMODULE)h, name);
		assert(f != nullptr);
		return f;
	}
#else
	void* load_library(const char_t* path)
	{
		void* h = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
		assert(h != nullptr);
		return h;
	}
	void* get_export(void* h, const char* name)
	{
		void* f = dlsym(h, name);
		assert(f != nullptr);
		return f;
	}
#endif

}

using initialize_fn         = void (*)(const char* scriptDllPath);
using loadScriptAssembly_fn = void (*)(const char* scriptDllPath);
using instantiate_fn        = void (*)(const char* typeName, cedar::Entity entity);
using removeScriptEntity_fn = void (*)(cedar::Entity entity);
using update_fn             = void (*)(float);
namespace Mean
{
#ifdef _WIN32
	template <typename TFunc>
	TFunc LoadFunctionPtr(void* InLibraryHandle, const char* InFunctionName)
	{
		auto result = (TFunc)GetProcAddress((HMODULE)InLibraryHandle, InFunctionName);
		return result;
	}
#else
	template <typename TFunc>
	TFunc LoadFunctionPtr(void* InLibraryHandle, const char* InFunctionName)
	{
		auto result = (TFunc)dlsym(InLibraryHandle, InFunctionName);
		return result;
	}
#endif

	void WaitForDebugger()
	{
#ifdef DEBUG_MODE
		CEDAR_INFO("Waiting for debugger to attach...");
	#ifdef WIN32
		while (!IsDebuggerPresent())
		{
			Sleep(100); // Sleep 100 ms to avoid busy waiting
		}
	#else
		bool debugger_present = false;
		while (!debugger_present)
		{
			if (ptrace(PTRACE_TRACEME, 0, nullptr, 0) == -1)
			{
				debugger_present = true;
			}
			else
			{
				ptrace(PTRACE_DETACH, 0, nullptr, 0);
			}

			usleep(100 * 1000); // sleep 100ms
		}
	#endif
		CEDAR_INFO("Debugger attached, continuing execution.");
#endif
	}

	// Globals to hold hostfxr exports
	hostfxr_set_error_writer_fn SetHostFXRErrorWriter = nullptr;
	// ErrorCallbackFn ErrorCallback = nullptr;

	hostfxr_initialize_for_runtime_config_fn init_for_config;
	hostfxr_get_runtime_delegate_fn get_delegate;
	hostfxr_close_fn close_fn;
	load_assembly_and_get_function_pointer_fn load_assembly_fn;
	get_function_pointer_fn get_fn_pointer;
	void* runtimeContext;

	//Unmanaged MeanScript functions that only the Engine can call
	initialize_fn initialize                        = nullptr;
	loadScriptAssembly_fn load_script_assembly      = nullptr;
	instantiate_fn instantiate_script               = nullptr;
	removeScriptEntity_fn removeScriptEntity_script = nullptr;
	update_fn update_scripts                        = nullptr;

	bool MeanScript::Init()
	{
		// Load hostfxr.dll
		// Pre-allocate a large buffer for the path to hostfxr
		char_t buffer[MAX_PATH];
		size_t buffer_size = sizeof(buffer) / sizeof(char_t);
		int rc             = get_hostfxr_path(buffer, &buffer_size, nullptr);
		if (rc != 0)
		{
			return false;
		}

		// Load hostfxr and get desired exports
		void* hostfxr = ::load_library(buffer);

		// Get function pointers
		init_for_config = LoadFunctionPtr<hostfxr_initialize_for_runtime_config_fn>(hostfxr, "hostfxr_initialize_for_runtime_config");
		get_delegate    = LoadFunctionPtr<hostfxr_get_runtime_delegate_fn>(hostfxr, "hostfxr_get_runtime_delegate");
		close_fn        = LoadFunctionPtr<hostfxr_close_fn>(hostfxr, "hostfxr_close");

		// Initialize runtime with .NET 5+ configuration
		const char_t* configPath = MEAN_STR("./meanscript.runtimeconfig.json");
		if (init_for_config(configPath, nullptr, &runtimeContext) != 0)
		{
			std::cerr << "Failed to initialize .NET runtime" << std::endl;
			return false;
		}

		// Get function pointer to load assemblies
		if (get_delegate(runtimeContext, hdt_load_assembly_and_get_function_pointer, (void**)&load_assembly_fn) != 0)
		{
			std::cerr << "Failed to get .NET assembly loader" << std::endl;
			return false;
		}

		// Get function pointer to load assemblies
		if (get_delegate(runtimeContext, hdt_get_function_pointer, (void**)&get_fn_pointer) != 0)
		{
			std::cerr << "Failed to get .NET assembly loader" << std::endl;
			return false;
		}

		int status = load_assembly_fn(
		    MEAN_STR("./MeanScripting.dll"),
		    MEAN_STR("MeanScriptEngine.MeanScriptEngine, MeanScripting"),
		    MEAN_STR("Initialize"),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    (void**)&initialize);

		status = load_assembly_fn(
		    MEAN_STR("./MeanScripting.dll"),
		    MEAN_STR("MeanScriptEngine.MeanScriptEngine, MeanScripting"),
		    MEAN_STR("InstantiateScriptToEntity"),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    (void**)&instantiate_script);

		status = load_assembly_fn(
		    MEAN_STR("./MeanScripting.dll"),
		    MEAN_STR("MeanScriptEngine.MeanScriptEngine, MeanScripting"),
		    MEAN_STR("RemoveScriptEntity"),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    (void**)&removeScriptEntity_script);

		status = load_assembly_fn(
		    MEAN_STR("./MeanScripting.dll"),
		    MEAN_STR("MeanScriptEngine.MeanScriptEngine, MeanScripting"),
		    MEAN_STR("OnUpdateAll"),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    (void**)&update_scripts);

		status = load_assembly_fn(
		    MEAN_STR("./MeanScripting.dll"),
		    MEAN_STR("MeanScriptEngine.MeanScriptEngine, MeanScripting"),
		    MEAN_STR("LoadDllScripts"),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    (void**)&load_script_assembly);

		SetupNativeBindings();

		WaitForDebugger();

		return true;
	}

	// typedef void (*bindNative_fn)(MeanNativeBindings);
	using bindNative_fn = void (*)(MeanNativeBindings);
	bool MeanScript::SetupNativeBindings()
	{
		MeanNativeBindings nativeBindings {};
		nativeBindings.SetEntityPositionFn = &Mean::SetEntityPosition;

		//Component bindings
		nativeBindings.GetTranformComponentFn = &Mean::GetTransformComponent;
		nativeBindings.GetComponentFn         = &Mean::GetComponent;
		nativeBindings.AddComponentFn         = &Mean::AddComponent;

		//Keyboard bindings
		nativeBindings.IsKeyPressedFn  = &cedar::Input::IsKeyPressed;
		nativeBindings.IsKeyReleasedFn = &cedar::Input::IsKeyReleased;
		nativeBindings.IsKeyRepeatedFn = &cedar::Input::IsKeyRepeated;

		//MeanString bindings
		nativeBindings.GetMeanStringFn     = &Mean::MeanString_GetString;
		nativeBindings.SetMeanStringfn     = &Mean::MeanString_SetString;
		nativeBindings.GetMeanStringSizeFn = &Mean::MeanString_GetSize;

		nativeBindings.LogFn = &Mean::Log;

		bindNative_fn bind = nullptr;
		int status         = load_assembly_fn(
            MEAN_STR("./MeanScripting.dll"),
            MEAN_STR("MeanScriptEngine.MeanNativeApi, MeanScripting"),
            MEAN_STR("BindNativeFunctions"),
            UNMANAGEDCALLERSONLY_METHOD,
            nullptr,
            (void**)&bind);

		if (status != 0)
		{
			return false;
		}

		bind(nativeBindings);

		return true;
	}

	void MeanScript::InitManagedScriptEngine(const std::string& scriptDllPath)
	{
		initialize(scriptDllPath.c_str());
	}

	void MeanScript::LoadScriptAssembly(const std::string& scriptDllPath)
	{
		load_script_assembly(scriptDllPath.c_str());
	}

	void MeanScript::AttachScriptToEntity(cedar::Entity entity, char* scriptName)
	{
		instantiate_script(scriptName, entity);
	}

	void MeanScript::RemoveScriptEntity(cedar::Entity entity)
	{
		removeScriptEntity_script(entity);
	}

	void MeanScript::OnUpdateAllScripts(float deltaTime)
	{
		update_scripts(deltaTime);
	}
}
// namespace Mean