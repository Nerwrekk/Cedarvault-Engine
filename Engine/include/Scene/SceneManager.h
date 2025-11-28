#pragma once

#include "Scene.h"

#include <unordered_map>

namespace cedar
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		static SceneManager* Get();

		Scene* CreateScene(std::string& name);
		void RemoveScene(std::string& name);

		Scene* GetActiveScene();
		void SetActiveScene(Scene* scene);
		void SetActiveScene(std::string& name);

	private:
		static SceneManager* s_sceneManager;
		Scene* m_activeScene = nullptr;
		std::unordered_map<std::string, Scene*> m_scenes;
	};

} // namespace cedar
