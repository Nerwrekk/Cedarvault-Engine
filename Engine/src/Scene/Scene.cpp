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

	LayerStack* Scene::GetLayerStack()
	{
		return &m_layerStack;
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
} // namespace cedar
