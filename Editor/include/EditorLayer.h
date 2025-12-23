#pragma once

#include "CedarVault.h"
#include "Panels/SceneHierarchy.h"
#include "Panels/AssetPanel.h"

namespace cedar
{
	class SceneHierarchyPanel;
	class EditorLayer : public Layer
	{
	public:
		DECL_TYPE_NAME(EditorLayer);

		EditorLayer()  = default;
		~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(IEvent& event) override;

		virtual void OnFixedUpdate(float fixedeltaTime) override;
		virtual void OnUpdate(float deltaTime) override;

		virtual void OnRender(float alpha) override; // for interpolation
		virtual void OnImGuiRender() override;

	private:
		SceneHierarchyPanel m_sceneHierarchyPanel {};
		AssetPanel m_assetPanel {};
	};
} // namespace cedar
