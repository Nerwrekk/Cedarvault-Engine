#pragma once

class SDL_Window;
class SDL_Renderer;

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
		Application();
		~Application();
		void Initialize();
		void Run();
		void Destroy();

	private:
		void ProccessInput();
		void Setup();
		void Update();
		void Render();

	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		bool m_isRunning = false;
		WindowInit windowInit;
		int previousMilliFrame;
	};

} // namespace cedar
