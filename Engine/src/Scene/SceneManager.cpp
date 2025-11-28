#include "Scene/SceneManager.h"

namespace cedar
{
	SceneManager* SceneManager::s_sceneManager = nullptr;
	SceneManager::SceneManager()
	{
		s_sceneManager = this;
	}

	SceneManager::~SceneManager()
	{
		for (auto [name, scene] : m_scenes)
		{
			CEDAR_DELETE(scene);
		}

		m_scenes.clear();
		m_activeScene = nullptr;
	}

	Scene* SceneManager::CreateScene(std::string& name)
	{
		auto scene     = new Scene(name);
		m_scenes[name] = scene;

		return scene;
	}

	Scene* SceneManager::GetActiveScene()
	{
		return m_activeScene;
	}

	void SceneManager::SetActiveScene(Scene* scene)
	{
		m_activeScene = scene;
	}

	void SceneManager::SetActiveScene(std::string& name)
	{
		auto scene = m_scenes.find(name);
		if (scene != m_scenes.end())
		{
			m_activeScene = scene->second;

			return;
		}

		CEDAR_FATAL("Tried to set active scene that did not exist, scene {}", name);
	}
}
// namespace cedar
