#include "imgui/ImGuiLayer.h"

#include "Application/Application.h"

// #include "GLFW/glfw3.h"
#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui/bindings/imgui_impl_opengl3.h"
#include "imgui/bindings/imgui_impl_sdlrenderer.h"
#include <imgui/bindings/imgui_impl_sdl.h>

namespace cedar
{
	ImGuiLayer::ImGuiLayer()
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnBeginRender()
	{
		// ImGui_ImplOpenGL3_NewFrame();
		// ImGui_ImplSDL2_NewFrame();
		// ImGui::NewFrame();

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::OnEndRender()
	{
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		//TODO: add when implementing opengl
		// ImGuiIO& io    = ImGui::GetIO();
		// io.DisplaySize = ImVec2((f32)m_context->GetWindow().GetWidth(), (f32)m_context->GetWindow().GetHeight());

		// // Rendering
		// ImGui::Render();
		// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		// {
		// 	// GLFWwindow* backup_current_context = glfwGetCurrentContext();
		// 	//We must set a backup here otherwise the whole rendering breaks! We solved it! :DD
		// 	auto backup_current_context = SDL_GL_GetCurrentContext();
		// 	ImGui::UpdatePlatformWindows();
		// 	ImGui::RenderPlatformWindowsDefault();
		// 	SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_context->GetWindow().GetNativeWindow()), backup_current_context);
		// 	// glfwMakeContextCurrent(backup_current_context);
		// }
	}

	void ImGuiLayer::OnAttach()
	{
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
		auto& app = Application::Get();
		ImGui_ImplSDL2_InitForSDLRenderer(app.GetWindow(), app.GetRenderer());
		ImGui_ImplSDLRenderer_Init(app.GetRenderer());
		// auto res = ImGui_sdl2(m_window, SDL_GL_GetCurrentContext());
		// ImGui_ImplOpenGL3_Init("#version 410");
		// m_renderSystem.reset(renderSystem);
	}

	//TODO: use this when we implement opengl Renderer!
	// void ImGuiLayer::OnAttach()
	// {
	// 	IMGUI_CHECKVERSION();
	// 	ImGui::CreateContext();
	// 	ImGuiIO& io = ImGui::GetIO();
	// 	(void)io;
	// 	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	// 	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // Enable Docking
	// 	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform Windows
	// 	// io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	// 	// io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	// 	ImGui::StyleColorsDark();

	// 	// AppLayer& app = AppLayer::Get();
	// 	SDL_Window* window = static_cast<SDL_Window*>(m_context->GetWindow().GetNativeWindow());

	// 	auto res = ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	// 	ImGui_ImplOpenGL3_Init("#version 410");
	// }

	void ImGuiLayer::OnDetach()
	{
		// ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	ImGuiContext* ImGuiLayer::GetImGuiContext()
	{
		return ImGui::GetCurrentContext();
	}
}
