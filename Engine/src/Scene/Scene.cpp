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

	LayerStack* Scene::GetLayerStack()
	{
		return &m_layerStack;
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
