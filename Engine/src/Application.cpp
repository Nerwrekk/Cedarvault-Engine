#include "Application.h"

#include "Common/Logger.h"
#include "Common/Constants.h"
#include "ECS/Systems/MovementSystem.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

namespace cedar
{
	Application::Application()
	{
		m_entityManager = std::make_unique<EntityManager>();
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

		// SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		m_isRunning = true;

		m_entityManager->AddSystem<MovementSystem>();
		m_entityManager->AddSystem<RenderSystem>();
		auto t = m_entityManager->GetSystem<RenderSystem>().get();
		m_renderSystem.reset(t);
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

		m_entityManager->UpdateAllSystems(deltaTime);

		m_entityManager->Update();
	}

	void Application::RenderCurrentLevel(const std::string& tileLevelMapId, int levelIndex)
	{
		TileLevelMap* tileLevelMap = AssetManager::Inst()->GetTileLevelMap(tileLevelMapId);

		const auto& map = AssetManager::Inst()->GetLevelMap(tileLevelMap->levelMapIds.at(levelIndex));
		int mapNumRows = map.size();
		for (int y = 0; y < mapNumRows; y++)
		{
			auto& colums = map.at(y);
			for (int x = 0; x < colums.size(); x++)
			{
				int positionXY = colums.at(x);
				int yPos = positionXY / 10;
				int xPos = positionXY % 10;
				SDL_Rect srcRect = {
					tileLevelMap->TileSize * xPos,
					tileLevelMap->TileSize * yPos,
					tileLevelMap->TileSize,
					tileLevelMap->TileSize
				};

				//Destination rectangle that we want to place our texture.
				//in order to scale the tilemap both the position and size must be multiplied by the scale
				SDL_Rect dstRect = {
					tileLevelMap->TileSize * x,
					tileLevelMap->TileSize * y,
					tileLevelMap->TileSize * static_cast<int>(tileLevelMap->TileScale),
					tileLevelMap->TileSize * static_cast<int>(tileLevelMap->TileScale)

				};

				SDL_RenderCopy(m_renderer, tileLevelMap->tilemap, &srcRect, &dstRect);
			}
		}
	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
		SDL_RenderClear(m_renderer);

		RenderCurrentLevel("JungleLevel", 0); //hardcoded for now;

		m_renderSystem->RenderEntites(m_renderer);

		SDL_RenderPresent(m_renderer);
	}

} // namespace cedar
