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

	// <SnippetLoadHostFxr>
	// Using the nethost library, discover the location of hostfxr and get exports
	bool load_hostfxr(const char_t* assembly_path)
	{
		get_hostfxr_parameters params { sizeof(get_hostfxr_parameters), assembly_path, nullptr };
		// Pre-allocate a large buffer for the path to hostfxr
		char_t buffer[MAX_PATH];
		size_t buffer_size = sizeof(buffer) / sizeof(char_t);
		int rc = get_hostfxr_path(buffer, &buffer_size, &params);
		if (rc != 0)
			return false;

		// Load hostfxr and get desired exports
		// NOTE: The .NET Runtime does not support unloading any of its native libraries. Running
		// dlclose/FreeLibrary on any .NET libraries produces undefined behavior.
		void* lib = load_library(buffer);
		init_for_cmd_line_fptr = (hostfxr_initialize_for_dotnet_command_line_fn)get_export(lib, "hostfxr_initialize_for_dotnet_command_line");
		init_for_config_fptr = (hostfxr_initialize_for_runtime_config_fn)get_export(lib, "hostfxr_initialize_for_runtime_config");
		get_delegate_fptr = (hostfxr_get_runtime_delegate_fn)get_export(lib, "hostfxr_get_runtime_delegate");
		run_app_fptr = (hostfxr_run_app_fn)get_export(lib, "hostfxr_run_app");
		close_fptr = (hostfxr_close_fn)get_export(lib, "hostfxr_close");

		return (init_for_config_fptr && get_delegate_fptr && close_fptr);
	}
	// </SnippetLoadHostFxr>

	// <SnippetInitialize>
	// Load and initialize .NET Core and get desired function pointer for scenario
	load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path)
	{
		// Load .NET Core
		void* load_assembly_and_get_function_pointer = nullptr;
		hostfxr_handle cxt = nullptr;
		int rc = init_for_config_fptr(config_path, nullptr, &cxt);
		if (rc != 0 || cxt == nullptr)
		{
			std::cerr << "Init failed: " << std::hex << std::showbase << rc << std::endl;
			close_fptr(cxt);
			return nullptr;
		}

		// Get the load assembly function pointer
		rc = get_delegate_fptr(
		    cxt,
		    hdt_load_assembly_and_get_function_pointer,
		    &load_assembly_and_get_function_pointer);
		if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
			std::cerr << "Get delegate failed: " << std::hex << std::showbase << rc << std::endl;

		close_fptr(cxt);
		return (load_assembly_and_get_function_pointer_fn)load_assembly_and_get_function_pointer;
	}
	// </SnippetInitialize>
}
using instantiate_fn = void (*)(const char* typeName, cedar::Entity entity);
using update_fn = void (*)(float);
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

	// Globals to hold hostfxr exports
	hostfxr_set_error_writer_fn SetHostFXRErrorWriter = nullptr;
	hostfxr_initialize_for_runtime_config_fn InitHostFXRForRuntimeConfig = nullptr;
	hostfxr_get_runtime_delegate_fn GetRuntimeDelegate = nullptr;
	hostfxr_close_fn CloseHostFXR = nullptr;

	// ErrorCallbackFn ErrorCallback = nullptr;

	hostfxr_initialize_for_runtime_config_fn init_for_config;
	hostfxr_get_runtime_delegate_fn get_delegate;
	hostfxr_close_fn close_fn;
	load_assembly_and_get_function_pointer_fn load_assembly_fn;
	get_function_pointer_fn get_fn_pointer;
	void* runtimeContext;

	instantiate_fn instantiate_script = nullptr;
	update_fn update_scripts = nullptr;

	bool MeanScript::Init()
	{
		// Load hostfxr.dll
		// Pre-allocate a large buffer for the path to hostfxr
		char_t buffer[MAX_PATH];
		size_t buffer_size = sizeof(buffer) / sizeof(char_t);
		int rc = get_hostfxr_path(buffer, &buffer_size, nullptr);
		if (rc != 0)
			return false;

		// Load hostfxr and get desired exports
		void* hostfxr = ::load_library(buffer);

		// Get function pointers
		init_for_config = (hostfxr_initialize_for_runtime_config_fn)get_export(hostfxr, "hostfxr_initialize_for_runtime_config");
		get_delegate = (hostfxr_get_runtime_delegate_fn)get_export(hostfxr, "hostfxr_get_runtime_delegate");
		close_fn = (hostfxr_close_fn)get_export(hostfxr, "hostfxr_close");

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
		    MEAN_STR("InstantiateScriptToEntity"),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    (void**)&instantiate_script);

		status = load_assembly_fn(
		    MEAN_STR("./MeanScripting.dll"),
		    MEAN_STR("MeanScriptEngine.MeanScriptEngine, MeanScripting"),
		    MEAN_STR("OnUpdateAll"),
		    UNMANAGEDCALLERSONLY_METHOD,
		    nullptr,
		    (void**)&update_scripts);

		SetupNativeBindings();

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
		nativeBindings.GetSpriteComponent = &Mean::GetSpriteComponent;
		nativeBindings.GetSpriteTextureId = &Mean::GetSpriteTextureId;

		//Keyboard bindings
		nativeBindings.IsKeyPressedFn = cedar::Input::IsKeyPressed;
		nativeBindings.IsKeyReleasedFn = cedar::Input::IsKeyReleased;
		nativeBindings.IsKeyRepeatedFn = cedar::Input::IsKeyRepeated;

		//MeanString bindings
		nativeBindings.GetMeanStringFn = &Mean::MeanString_GetString;
		nativeBindings.SetMeanStringfn = &Mean::MeanString_SetString;
		nativeBindings.GetMeanStringSizeFn = &Mean::MeanString_GetSize;

		bindNative_fn bind = nullptr;
		int status = load_assembly_fn(
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

	void MeanScript::AttachScriptToEntity(cedar::Entity entity, char* scriptName)
	{
		instantiate_script(scriptName, entity);
	}
	void MeanScript::OnUpdateAllScripts(float deltaTime)
	{
		update_scripts(deltaTime);
	}
}
// namespace Mean