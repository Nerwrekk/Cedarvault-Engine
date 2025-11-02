#include "Application/Application.h"

#include "Common/Logger.h"
#include "Common/Constants.h"
#include "ECS/Systems/MovementSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/ScriptSystem.h"
#include "ECS/Systems/MeanScriptSystem.h"
#include "ECS/Systems/RenderBoxColliderSystem.h"
#include "ECS/Systems/CameraFollowSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "Common/Input.h"
#include "Common/CedarTime.h"
#include "Common/AssetManager.h"

#include "imgui.h"
#include "imgui/bindings/imgui_impl_opengl3.h"
#include "imgui/bindings/imgui_impl_sdlrenderer.h"
#include <imgui/bindings/imgui_impl_sdl.h>
#include <glm/glm.hpp>
#include <iostream>

namespace cedar
{
	Application* Application::s_Application = nullptr;
	Application::Application()
	{
		m_entityManager = std::make_unique<EntityManager>();
		m_eventBus      = std::make_unique<EventBus>();
		// m_luieScriptEngine = std::make_unique<Luie::ScriptEngine>();

		s_Application = this;
		Initialize();
	}

	Application::~Application()
	{
		Destroy();
	}

	Application& Application::Get()
	{
		return *s_Application;
	}

	SDL_Renderer* Application::GetRenderer() const
	{
		return m_renderer;
	}

	void Application::Initialize()
	{
		Mean::MeanScript::Init();

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			CEDAR_FATAL("Error init SDL");

			return;
		}

		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);
		windowInit.WindowWidth  = 800;
		windowInit.WindowHeight = 600;

		m_window = SDL_CreateWindow(
		    "Game",
		    SDL_WINDOWPOS_CENTERED,
		    SDL_WINDOWPOS_CENTERED,
		    windowInit.WindowWidth,
		    windowInit.WindowHeight,
		    0);

		GameSetting.WindowWidth  = windowInit.WindowWidth;
		GameSetting.WindowHeight = windowInit.WindowHeight;

		//SDL will be smart enough to go and take advantage of accelerated graphics by whatever is avaiable on the current maching
		//its thanks to the flag SDL_RENDERER_ACCELERATED, but it will be activated by default
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_renderer)
		{
			CEDAR_FATAL("Error creating SDL renderer");

			return;
		}

		//Init the camera
		m_camera.PrevX  = 0;
		m_camera.PrevY  = 0;
		m_camera.Rect.x = 0;
		m_camera.Rect.y = 0;
		m_camera.Rect.w = windowInit.WindowWidth;
		m_camera.Rect.h = windowInit.WindowHeight;

		Input::InitKeyStates();

		// SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		m_isRunning = true;

		// m_luieScriptEngine->Initialize();

		m_entityManager->AddSystem<MovementSystem>();
		m_entityManager->AddSystem<AnimationSystem>();
		m_entityManager->AddSystem<MeanScriptSystem>();
		m_entityManager->AddSystem<CollisionSystem>();
		m_entityManager->AddSystem<CameraFollowSystem>();
		m_entityManager->AddSystem<RenderBoxColliderSystem>();
		m_entityManager->AddSystem<RenderSystem>();

		//m_entityManager->AddSystem<ScriptSystem>(m_luieScriptEngine.get());

		auto renderSystem = m_entityManager->GetSystem<RenderSystem>().get();
		m_renderSystem.reset(renderSystem);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform Windows
		// io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		// io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
		ImGui_ImplSDLRenderer_Init(m_renderer);
		// auto res = ImGui_sdl2(m_window, SDL_GL_GetCurrentContext());
		// ImGui_ImplOpenGL3_Init("#version 410");
		// m_renderSystem.reset(renderSystem);
	}

	void Application::Run()
	{
		uint64_t prevCounter = SDL_GetPerformanceCounter();
		double accumulator   = 0.0;

		while (m_isRunning)
		{
			// time
			uint64_t nowCounter = SDL_GetPerformanceCounter();
			double frameTime    = double(nowCounter - prevCounter) / double(SDL_GetPerformanceFrequency());
			prevCounter         = nowCounter;

			if (frameTime > MAX_ACCUM)
			{
				frameTime = MAX_ACCUM;
			}
			accumulator += frameTime;

			ProccessInput();

			// --- fixed update step ---
			int updates = 0;
			while (accumulator >= FIXED_DT && updates < MAX_UPDATES_PER_FRAME)
			{
				// Tell components/systems to snapshot previous state for interpolation.
				m_entityManager->SnapshotPreviousState();

				// Run game logic with fixed dt
				Update(static_cast<float>(FIXED_DT));

				m_entityManager->Update(); //treat it as FlushCommandBuffers

				accumulator -= FIXED_DT;
				updates++;
			}

			// If we've hit the cap, drop remaining accumulator to avoid spiraling
			if (updates == MAX_UPDATES_PER_FRAME)
			{
				accumulator = 0.0;
			}

			// interpolation factor [0,1)
			float alpha = static_cast<float>(accumulator / FIXED_DT);

			// Render using interpolation
			Render(alpha);

			// Present is in Render(); you can delay here if you prefer
			// Optional: small sleep to avoid busy loop if not using vsync
			// SDL_Delay(1); // tiny yield — optional
		}
	}

	void Application::Destroy()
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		ImGui::DestroyContext();
		ImGui_ImplSDL2_Shutdown();

		SDL_Quit();
	}

	Camera* Application::GetMainCamera()
	{
		return &m_camera;
	}

	void Application::ProccessInput()
	{
		Input::UpdateKeyStates();

		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent))
		{
			ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				m_isRunning = false;
				break;
			//===== KEYBOARD EVENTS =====
			case SDL_KEYDOWN: // A key was pressed.
				sdlEvent.key.repeat ? m_eventBus->PostEvent<KeyRepeatEvent>(KeyRepeatEvent(sdlEvent.key.keysym.sym)) :
				                      m_eventBus->PostEvent<KeyPressEvent>(KeyPressEvent(sdlEvent.key.keysym.sym));

				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					m_isRunning = false;
				}
				break;
			case SDL_KEYUP: // A key was released.
				m_eventBus->PostEvent<KeyReleaseEvent>(KeyReleaseEvent(sdlEvent.key.keysym.sym));
				break;
			}
		}
	}

	//Update game objects
	void Application::Update(float dt)
	{
		Time::DeltaTime = dt;

		// process queued events (from input -> event bus)
		m_eventBus->PollEvents();

		m_entityManager->UpdateAllSystems();

		m_entityManager->LateUpdateAllSystems();
	}

	void Application::RenderCurrentLevel(const std::string& tileLevelMapId, int levelIndex)
	{
		TileLevelMap* tileLevelMap = AssetManager::Inst()->GetTileLevelMap(tileLevelMapId);

		const auto& map = AssetManager::Inst()->GetLevelMap(tileLevelMap->levelMapIds.at(levelIndex));
		auto mapNumRows = map.size();
		for (int y = 0; y < mapNumRows; y++)
		{
			auto& colums = map.at(y);
			for (int x = 0; x < colums.size(); x++)
			{
				int positionXY   = colums.at(x);
				int yPos         = positionXY / 10;
				int xPos         = positionXY % 10;
				SDL_Rect srcRect = {
					tileLevelMap->TileSize * xPos,
					tileLevelMap->TileSize * yPos,
					tileLevelMap->TileSize,
					tileLevelMap->TileSize
				};

				//Destination rectangle that we want to place our texture.
				//in order to scale the tilemap both the position and size must be multiplied by the scale
				SDL_Rect dstRect = {
					(tileLevelMap->TileSize * static_cast<int>(tileLevelMap->TileScale)) * x - static_cast<int>(m_camera.Rect.x),
					(tileLevelMap->TileSize * static_cast<int>(tileLevelMap->TileScale)) * y - static_cast<int>(m_camera.Rect.y),
					tileLevelMap->TileSize * static_cast<int>(tileLevelMap->TileScale),
					tileLevelMap->TileSize * static_cast<int>(tileLevelMap->TileScale)

				};

				SDL_RenderCopy(m_renderer, tileLevelMap->tilemap, &srcRect, &dstRect);
			}
		}
	}

	void Application::Render(float alpha)
	{
		Time::AlphaTime = alpha;

		SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
		SDL_RenderClear(m_renderer);

		RenderCurrentLevel(GameSetting.CurrentLevel, GameSetting.CurrentLevelIndex);

		m_entityManager->RenderUpdateAllSystems(m_renderer);

		m_renderSystem->RenderEntites(m_renderer, alpha);

		//TODO: fix proper imgui rendering
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(m_renderer);
		// ImGui::EndFrame();
	}

} // namespace cedar
