#pragma once

#include "CedarVault.h"

namespace cedar
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel()  = default;
		~SceneHierarchyPanel() = default;

		void DrawSceneHierarchy(Scene* scene);

	private:
		void DrawEntityNode(Entity entity, Scene* scene);

	private:
		Entity m_selectedEntity { UINT32_MAX }; //setting max value so no pre existing entity will already be selected
	};
} // namespace cedar
