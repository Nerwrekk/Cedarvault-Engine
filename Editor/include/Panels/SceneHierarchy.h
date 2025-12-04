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
		void DrawEntityNode(Entity entity);

	private:
		Entity m_selectedEntity { 0 };
	};
} // namespace cedar
