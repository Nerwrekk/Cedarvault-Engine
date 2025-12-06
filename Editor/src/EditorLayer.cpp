#include "EditorLayer.h"

namespace cedar
{
	void EditorLayer::OnAttach()
	{
		//TODO: move this to somewere better later
		SDL_SetTextureScaleMode(Application::Get().m_FrameBuffer, SDL_ScaleModeNearest); //this is good for rendering pixel art
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnEvent(IEvent& event)
	{
	}

	void EditorLayer::OnFixedUpdate(float fixedeltaTime)
	{
	}

	void EditorLayer::OnRender(float alpha)
	{
	}

	static void DrawGameViewport()
	{
		ImGui::Begin("Game");

		ImVec2 size = ImGui::GetContentRegionAvail();
		ImGui::Image((ImTextureID)Application::Get().m_FrameBuffer, size);

		ImGui::End();
	}

	void EditorLayer::OnImGuiRender()
	{
		auto scene = cedar::SceneManager::Get()->GetActiveScene();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		m_sceneHierarchyPanel.DrawSceneHierarchy(scene);

		DrawGameViewport();
	}
}