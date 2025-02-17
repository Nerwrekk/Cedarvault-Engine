#pragma once

#include "Common/Core.h"
#include "ECS/ECS.h"
#include "ECS/Systems/RenderSystem.h"

#include <functional>
#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace cedar
{
	struct WindowInit
	{
		int WindowWidth;
		int WindowHeight;
	};

	class Application
	{
	public:
		CEDAR_API Application();
		CEDAR_API ~Application();
		void Initialize();
		//Use setup to initialize entities before the game runs
		template <typename TCallable>
		void Setup(TCallable func)
		{
			func();
		}
		void Run();
		void Destroy();

		EntityManager* Manager()
		{
			return m_entityManager.get();
		}

		SDL_Renderer* GetRenderer() const
		{
			return m_renderer;
		}

	private:
		void ProccessInput();
		void Update();
		void RenderCurrentLevel(const std::string& tileLevelMapId, int levelIndex);
		void Render();

	private:
		std::unique_ptr<EntityManager> m_entityManager;
		std::shared_ptr<RenderSystem> m_renderSystem;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		WindowInit windowInit;
		bool m_isRunning = false;
		//Note to self to remember to always pre-initialize fields in a class!
		int previousMilliFrame = 0;
	};

} // namespace cedar
