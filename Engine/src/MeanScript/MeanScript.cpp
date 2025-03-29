#include "MeanScript/MeanScript.h"

// #include "MeanScript/host/nethost.h"
// #include "MeanScript/host/coreclr_delegates.h"
// #include "MeanScript/host/hostfxr.h"

// #define __NETHOST_H__

#include <Windows.h>

#include <nethost.h>
#include <coreclr_delegates.h>
#include <hostfxr.h>

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

namespace Mean
{
	// Globals to hold hostfxr exports
	hostfxr_initialize_for_runtime_config_fn init_for_config;
	hostfxr_run_app_fn hostfxr_run;
	hostfxr_get_runtime_delegate_fn get_delegate;
	hostfxr_close_fn close_fn;
	load_assembly_and_get_function_pointer_fn load_assembly_fn;
	void* runtimeContext;

	bool MeanScript::Init()
	{
		// Load hostfxr.dll dynamically
		HMODULE hHostfxr = LoadLibraryW(L"C:\\Program Files (x86)\\Windows Kits\\10\\Windows Performance Toolkit\\hostfxr.dll"); // Adjust the path as needed

		if (hHostfxr == nullptr)
		{
			std::cerr << "Failed to load hostfxr.dll." << std::endl;
			return 1;
		}

		// Get the function pointer for hostfxr_initialize_for_runtime_config
		init_for_config = (hostfxr_initialize_for_runtime_config_fn)GetProcAddress(hHostfxr, "hostfxr_initialize_for_runtime_config");

		// Path to the .NET Core application (e.g., directory containing runtimeconfig.json)
		const char_t* appPath = L"C:\\dev\\MyCSharpScript\\bin\\Release\\net8.0\\win-x64\\publish";
		// const char_t* appPath = L"./";

		// Initialize the hostfxr API
		hostfxr_handle hostfxr = nullptr;
		int result = init_for_config(appPath, nullptr, &hostfxr);

		if (result != 0 || hostfxr == nullptr)
		{
			std::cerr << "Failed to initialize .NET Core runtime." << std::endl;
			return 1;
		}

		// Start the runtime
		result = hostfxr_run(hostfxr);

		if (result != 0)
		{
			std::cerr << "Failed to run .NET Core application." << std::endl;
		}
		else
		{
			std::cout << ".NET Core application running successfully." << std::endl;
		}

		// Clean up
		close_fn(hostfxr);

		return true;
	}

} // namespace Mean