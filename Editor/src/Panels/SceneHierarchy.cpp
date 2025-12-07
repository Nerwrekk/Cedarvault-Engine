#include "Panels/SceneHierarchy.h"

#include <glm/gtc/type_ptr.hpp>

namespace cedar
{
	void SceneHierarchyPanel::DrawSceneHierarchy(Scene* scene)
	{
		ImGui::Begin("Scene Hierarchy");

		for (auto entity : scene->GetEntityRegister()->GetAllEntities())
		{
			DrawEntityNode(entity);
		}

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_selectedEntity = Entity(UINT32_MAX);
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

		ImGui::Begin("Properties");
		if (m_selectedEntity.GetId() != UINT32_MAX)
		{
			DrawEntityComponents(m_selectedEntity);
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
			entity.Kill();
			if (m_selectedEntity == entity)
			{
				m_selectedEntity = Entity(UINT32_MAX);
			}
		}
	}

	void SceneHierarchyPanel::DrawEntityComponents(Entity entity)
	{
		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)TypeIdOf<TransformComponent>(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto transform = entity.GetComponent<TransformComponent>();

				if (ImGui::DragFloat2("Position", glm::value_ptr(transform->Position), .1f))
				{
				}

				if (ImGui::DragFloat2("Scale", glm::value_ptr(transform->Scale), .1f))
				{
				}

				auto rotation = static_cast<float>(transform->Rotation);
				if (ImGui::DragFloat("Rotation", &rotation, 0.1f, .5f))
				{
					transform->Rotation = rotation;
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<BoxColliderComponent>())
		{
			if (ImGui::TreeNodeEx((void*)TypeIdOf<BoxColliderComponent>(), ImGuiTreeNodeFlags_DefaultOpen, "BoxCollider"))
			{
				auto boxCollider = entity.GetComponent<BoxColliderComponent>();

				if (ImGui::DragInt("Width", &boxCollider->Width, .1f))
				{
				}

				if (ImGui::DragInt("Height", &boxCollider->Height, .1f))
				{
				}

				if (ImGui::DragFloat2("Offset", glm::value_ptr(boxCollider->Offset), .1f))
				{
				}

				ImGui::TreePop();
			}
		}
	}
} // namespace cedar
