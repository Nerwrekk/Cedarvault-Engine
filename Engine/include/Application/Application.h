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
	class SceneManager;

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

	enum class AppMode
	{
		Editor,
		Game
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

		SDL_Renderer* GetRenderer() const;

		SDL_Window* GetWindow() const;

		Luie::ScriptEngine* GetScriptEngine() const
		{
			return m_luieScriptEngine.get();
		}

		void RaiseEvent(IEvent& event);

		Camera* GetMainCamera();

		void RenderCurrentLevel(const std::string& tileLevelMapId, int levelIndex);

		void SetAppMode(AppMode mode);

	public:
		GameSettings GameSetting;
		SDL_Texture* m_FrameBuffer;

	private:
		void ProccessInputAndPollOsEvents();

	protected:
		std::unique_ptr<EventBus> m_eventBus;
		std::unique_ptr<AssetManager> m_assetManager;
		SDL_Renderer* m_renderer;
		std::unique_ptr<SceneManager> m_sceneManager;

	private:
		std::unique_ptr<Luie::ScriptEngine> m_luieScriptEngine;
		std::unique_ptr<ImGuiLayer> m_imGuiLayer;
		SDL_Window* m_window;
		WindowInit windowInit;
		bool m_isRunning = false;
		//Note to self to remember to always pre-initialize fields in a class!
		int previousMilliFrame = 0;
		Camera m_camera;
		AppMode m_mode;

		static Application* s_Application;
	};

	// To be defined in CLIENT
	Application* CreateApplication(); //TODO Add args later

} // namespace cedar
