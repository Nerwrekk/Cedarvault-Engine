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
		WindowInit windowInit;
		bool m_isRunning = false;
		//Note to self to remember to always pre-initialize fields in a class!
		int previousMilliFrame = 0;
	};

} // namespace cedar
