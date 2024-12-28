#include "Application.h"

#include "ECS/ECS.h"
#include "Common/Logger.h"
#include "Common/Constants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
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
			CEDAR_FATAL("Error init SDL");

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
			CEDAR_FATAL("Error creating SDL renderer");

			return;
		}

		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		m_isRunning = true;
	}

	//Initialize game object
	void Application::Setup()
	{
		EntityManager::Instance()->Initialize();
	}

	void Application::Run()
	{
		Setup();
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

	//Update game objects
	void Application::Update()
	{
		//Locks execution until we meet out milliseconds criteria
		int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - previousMilliFrame);
		if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
		{
			SDL_Delay(timeToWait);
		}

		//difference in ticks from last frame, converted to seconds
		double deltaTime = (SDL_GetTicks() - previousMilliFrame) / 1000.f;

		previousMilliFrame = SDL_GetTicks();

		// playerPos.x += playerVelocity.x * deltaTime;
		// playerPos.y += playerVelocity.y * deltaTime;
	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
		SDL_RenderClear(m_renderer);

		// SDL_Surface* surface = IMG_Load("../Game/assets/images/tank-tiger-right.png");
		// SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		// SDL_FreeSurface(surface);

		// //Destination rectangle that we want to place our texture.
		// SDL_Rect dstRect = { static_cast<int>(playerPos.x), static_cast<int>(playerPos.y), 32, 32 };
		// SDL_RenderCopy(m_renderer, texture, nullptr, &dstRect);

		// SDL_DestroyTexture(texture);

		SDL_RenderPresent(m_renderer);
	}

} // namespace cedar
