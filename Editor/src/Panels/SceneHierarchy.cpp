#include "Panels/SceneHierarchy.h"

namespace cedar
{
	void SceneHierarchyPanel::DrawSceneHierarchy(Scene* scene)
	{
		ImGui::Begin("Scene Hierarchy");

		for (auto entity : scene->GetEntityRegister()->GetAllEntities())
		{
			DrawEntityNode(entity);
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		std::string label = "Entity" + std::to_string(entity.GetId());

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

		if (m_selectedEntity.GetId() == entity.GetId())
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity.GetId(), flags, label.c_str());
		if (ImGui::IsItemClicked())
		{
			m_selectedEntity = entity;
			CEDAR_INFO("selected entity: {}", m_selectedEntity.GetId());
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}
} // namespace cedar
