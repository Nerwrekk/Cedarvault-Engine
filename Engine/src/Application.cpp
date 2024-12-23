#include "Application.h"

#include <SDL2/SDL.h>
#include <iostream>

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
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cerr << "Error init SDL" << std::endl;

			return;
		}

		m_window = SDL_CreateWindow(
		    "Game",
		    SDL_WINDOWPOS_CENTERED,
		    SDL_WINDOWPOS_CENTERED,
		    800,
		    600,
		    SDL_WINDOW_BORDERLESS);

		m_renderer = SDL_CreateRenderer(
		    m_window,
		    -1, //Get default one
		    0   //no flags
		);

		if (!m_renderer)
		{
			std::cerr << "Error creating SDL renderer" << std::endl;
		}
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
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);

		SDL_Quit();
	}

	void Application::ProccessInput()
	{
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			}
		}
	}

	void Application::Update()
	{
	}

	void Application::Render()
	{
	}

} // namespace cedar
