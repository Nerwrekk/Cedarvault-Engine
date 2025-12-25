#include "EditorLayer.h"

namespace cedar
{
	void EditorLayer::OnAttach()
	{
		//TODO: move this to somewere better later
		// SDL_SetTextureScaleMode(Application::Get().m_FrameBuffer, SDL_ScaleModeNearest); //this is good for rendering pixel art
		// SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnEvent(IEvent& event)
	{
	}

	void EditorLayer::OnFixedUpdate(float fixedeltaTime)
	{
		auto scene = SceneManager::Get()->GetActiveScene();

		// Important: snapshot before fixed updates so systems can interpolate later.
		scene->GetEntityRegister()->SnapshotPreviousState();

		scene->FixedUpdateAllSystems(static_cast<float>(FIXED_DT));
	}

	void EditorLayer::OnUpdate(float deltaTime)
	{
		auto scene = SceneManager::Get()->GetActiveScene();

		scene->UpdateAllSystems(Time::DeltaTime);

		scene->LateUpdateAllSystems();

		scene->Update();
	}

	void EditorLayer::OnRender(float alpha)
	{
		auto scene = SceneManager::Get()->GetActiveScene();

		scene->RenderUpdateAllSystems(Time::AlphaTime);
	}

	static void DrawGameViewport()
	{
		ImGui::Begin("Game");

		// ImVec2 size = ImGui::GetContentRegionAvail();
		auto gameWidth  = Application::Get().GameSetting.WindowWidth;
		auto gameHeight = Application::Get().GameSetting.WindowHeight;

		ImVec2 avail = ImGui::GetContentRegionAvail();

		float gameAspect  = (float)gameWidth / (float)gameHeight;
		float availAspect = avail.x / avail.y;

		ImVec2 imageSize;
		if (availAspect > gameAspect)
		{
			imageSize.y = avail.y;
			imageSize.x = avail.y * gameAspect;
		}
		else
		{
			imageSize.x = avail.x;
			imageSize.y = avail.x / gameAspect;
		}

		ImGui::SetCursorPosX((avail.x - imageSize.x) * 0.5f);
		ImGui::SetCursorPosY((avail.y - imageSize.y) * 0.5f);

		ImGui::Image((ImTextureID)Application::Get().m_FrameBuffer, imageSize);

		ImGui::End();
	}

	void EditorLayer::OnImGuiRender()
	{
		auto scene = cedar::SceneManager::Get()->GetActiveScene();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		m_sceneHierarchyPanel.DrawSceneHierarchy(scene);

		m_assetPanel.DrawAssetPanel();

		DrawGameViewport();
	}
}