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

		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);
		windowInit.WindowWidth = 800;
		windowInit.WindowHeight = 600;

		m_window = SDL_CreateWindow(
		    "Game",
		    SDL_WINDOWPOS_CENTERED,
		    SDL_WINDOWPOS_CENTERED,
		    windowInit.WindowWidth,
		    windowInit.WindowHeight,
		    SDL_WINDOW_BORDERLESS);

		m_renderer = SDL_CreateRenderer(
		    m_window,
		    -1,                                                  //Get default one
		    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //no flags
		);

		if (!m_renderer)
		{
			std::cerr << "Error creating SDL renderer" << std::endl;

			return;
		}

		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		m_isRunning = true;
	}

	void Application::Run()
	{
		while (m_isRunning)
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
			case SDL_QUIT:
				m_isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					m_isRunning = false;
				}
				break;
			}
		}
	}

	void Application::Update()
	{
	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		SDL_RenderClear(m_renderer);

		SDL_RenderPresent(m_renderer);
	}

} // namespace cedar
