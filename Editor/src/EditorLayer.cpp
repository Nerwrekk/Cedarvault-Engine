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

	void EditorLayer::OnImGuiRender()
	{
		auto scene = cedar::SceneManager::Get()->GetActiveScene();
		m_sceneHierarchyPanel.DrawSceneHierarchy(scene);
	}
}