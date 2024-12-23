#pragma once

class SDL_Window;
class SDL_Renderer;

namespace cedar
{
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
		void Update();
		void Render();

	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		bool IsRunning;
	};

} // namespace cedar
