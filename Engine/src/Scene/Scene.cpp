#include "Scene/Scene.h"

namespace cedar
{
	Scene::Scene()
	{
		m_sceneName = "DefaultScene";
	}
	Scene::Scene(std::string& name)
	{
		m_sceneName = name;
	}

	Entity Scene::CreateEntity()
	{
		return m_entityRegistry.CreateEntity();
	}

	EntityManager* Scene::GetEntityRegister()
	{
		return &m_entityRegistry;
	}

	void Scene::SetSceneName(std::string& name)
	{
		m_sceneName = name;
	}

	std::string& Scene::GetSceneName()
	{
		return m_sceneName;
	}

	void Scene::FixedUpdateAllSystems(float fixedDeltaTime)
	{
		if (m_isPaused)
		{
			return;
		}

		m_entityRegistry.FixedUpdateAllSystems(fixedDeltaTime);
	}

	void Scene::UpdateAllSystems(float deltaTime)
	{
		if (m_isPaused)
		{
			return;
		}

		m_entityRegistry.UpdateAllSystems(deltaTime);
	}

	void Scene::LateUpdateAllSystems()
	{
		if (m_isPaused)
		{
			return;
		}

		m_entityRegistry.LateUpdateAllSystems();
	}

	void Scene::RenderUpdateAllSystems(SDL_Renderer* renderer, float alpha)
	{
		if (m_isPaused)
		{
			return;
		}

		m_entityRegistry.RenderUpdateAllSystems(renderer, alpha);
	}

	void Scene::Update()
	{
		if (m_isPaused)
		{
			return;
		}

		m_entityRegistry.Update();
	}

	void Scene::SetPaused(bool paused)
	{
		m_isPaused = paused;
	}

	bool Scene::IsPaused() const
	{
		return m_isPaused;
	}
} // namespace cedar
