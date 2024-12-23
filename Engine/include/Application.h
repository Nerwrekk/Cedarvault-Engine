#pragma once

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
	};

} // namespace cedar
