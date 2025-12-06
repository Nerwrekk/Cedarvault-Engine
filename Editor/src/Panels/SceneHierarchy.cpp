#include "Panels/SceneHierarchy.h"

namespace cedar
{
	void SceneHierarchyPanel::DrawSceneHierarchy(Scene* scene)
	{
		ImGui::Begin("Scene Hierarchy");

		for (auto entity : scene->GetEntityRegister()->GetAllEntities())
		{
			DrawEntityNode(entity, scene);
		}

		//right-click on blank space
		if (ImGui::BeginPopupContextWindow(0, ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem("Create Entity"))
			{
				scene->GetEntityRegister()->CreateEntity();
			}

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity, Scene* scene)
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

		bool isEntityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				isEntityDeleted = true;
			}

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (isEntityDeleted)
		{
			scene->GetEntityRegister()->KillEntity(entity);
			if (m_selectedEntity == entity)
			{
				m_selectedEntity = Entity(UINT32_MAX);
			}
		}
	}
} // namespace cedar
