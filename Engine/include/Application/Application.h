#pragma once

#include "Common/Core.h"
#include "ECS/ECS.h"
#include "Common/Event/EventBus.h"
#include "Common/AssetManager.h"
#include "Luie/Luie.h"
#include "Camera.h"
#include "Common/SDL_Wrapper.h"
#include "Common/LayerStack.h"
#include "imgui.h"

#include <functional>
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

namespace cedar
{
	//Note! If you need to forward declare a class or a struct thats within a namespace,
	//you need to make sure that you include that namespace or declare it within that namespace!
	class RenderSystem;
	class LayerStack;
	class ImGuiLayer;

	struct WindowInit
	{
		int WindowWidth;
		int WindowHeight;
	};

	struct GameSettings
	{
		int WindowWidth;
		int WindowHeight;
		int MapWidth;
		int MapHeight;
		std::string CurrentLevel;
		int CurrentLevelIndex;
	};

	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Initialize();
		void Run();
		void Destroy();

		static Application& Get();

		EntityManager* Manager()
		{
			return m_entityManager.get();
		}

		SDL_Renderer* GetRenderer() const;

		SDL_Window* GetWindow() const;

		Luie::ScriptEngine* GetScriptEngine() const
		{
			return m_luieScriptEngine.get();
		}

		template <typename TLayer, typename... Args>
		TLayer* PushLayer(Args&&... args);

		Camera* GetMainCamera();

		void RenderCurrentLevel(const std::string& tileLevelMapId, int levelIndex);

	public:
		GameSettings GameSetting;

	private:
		void ProccessInput();
		void Update(float dt);
		void Render(float interpolation);

	protected:
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<EventBus> m_eventBus;
		std::unique_ptr<AssetManager> m_assetManager;
		std::shared_ptr<RenderSystem> m_renderSystem;
		SDL_Renderer* m_renderer;

	private:
		std::unique_ptr<Luie::ScriptEngine> m_luieScriptEngine;
		LayerStack m_layerStack;
		std::unique_ptr<ImGuiLayer> m_imGuiLayer;
		SDL_Window* m_window;
		WindowInit windowInit;
		bool m_isRunning = false;
		//Note to self to remember to always pre-initialize fields in a class!
		int previousMilliFrame = 0;
		Camera m_camera;

		static Application* s_Application;
	};

	template <typename TLayer, typename... Args>
	TLayer* Application::PushLayer(Args&&... args)
	{
		return m_layerStack.PushLayer<TLayer>(std::forward<Args>(args)...);
	}

	// To be defined in CLIENT
	Application* CreateApplication(); //TODO Add args later

} // namespace cedar
