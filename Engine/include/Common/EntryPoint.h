#pragma once
#include "Application/Application.h"

extern cedar::Application* cedar::CreateApplication();

int main(int argc, char** argv)
{
	//TODO: Add profiling
	// CEDAR_PROFILE_BEGIN_SESSION("Startup", "CedarProfile-Startup.json");
	auto app = cedar::CreateApplication();
	// CEDAR_PROFILE_END_SESSION();

	// CEDAR_PROFILE_BEGIN_SESSION("Runtime", "CedarProfile-Runtime.json");
	app->Run();
	// CEDAR_PROFILE_END_SESSION();

	// CEDAR_PROFILE_BEGIN_SESSION("Shutdown", "CedarProfile-Shutdown.json");
	delete app;
	// CEDAR_PROFILE_END_SESSION();
}
