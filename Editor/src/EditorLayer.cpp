#include "EditorLayer.h"

namespace cedar
{
	void EditorLayer::OnAttach()
	{
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

	static void docking()
	{
		ImGuiWindowFlags window_flags =
		    ImGuiWindowFlags_NoDocking |
		    ImGuiWindowFlags_NoTitleBar |
		    ImGuiWindowFlags_NoCollapse |
		    ImGuiWindowFlags_NoResize |
		    ImGuiWindowFlags_NoMove |
		    ImGuiWindowFlags_NoBringToFrontOnFocus |
		    ImGuiWindowFlags_NoNavFocus;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		ImGui::Begin("Dockspace", nullptr, window_flags);
		ImGui::PopStyleVar(2);

		ImGuiID dockspace_id = ImGui::GetID("DockspaceID");
		ImGui::DockSpace(dockspace_id, ImVec2(0, 0));

		ImGui::End();
	}

	void EditorLayer::OnImGuiRender()
	{
		auto scene = cedar::SceneManager::Get()->GetActiveScene();
		m_sceneHierarchyPanel.DrawSceneHierarchy(scene);
	}
}