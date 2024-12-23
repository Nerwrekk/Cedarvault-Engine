#include "Application.h"

namespace cedar
{
	Application::Application()
	{
		Initialize();
	}

	Application::~Application()
	{
		Destroy();
	}

	void Application::Initialize()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			ProccessInput();
			Update();
			Render();
		}
	}

	void Application::Destroy()
	{
	}

	void Application::ProccessInput()
	{
	}

	void Application::Update()
	{
	}

	void Application::Render()
	{
	}

} // namespace cedar
