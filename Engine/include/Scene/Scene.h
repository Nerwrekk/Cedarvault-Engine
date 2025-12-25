#pragma once

#include "ECS/ECS.h"

namespace cedar
{
	class SceneManager;

	class Scene
	{
	public:
		Entity CreateEntity();
		void KillEntity(Entity entity);

		EntityManager* GetEntityRegister();

		void SetSceneName(std::string& name);
		std::string& GetSceneName();

		template <typename TComponent, typename... TArgs>
		void AddComponent(Entity entity, TArgs&&... args);

		template <typename TComponent>
		void RemoveComponent(Entity entity);

		template <typename TComponent>
		bool HasComponent(Entity entity) const;

		void FixedUpdateAllSystems(float fixedDeltaTime);
		void UpdateAllSystems(float deltaTime);
		void LateUpdateAllSystems();
		void RenderUpdateAllSystems(float alpha);
		void Update();

		void SetPaused(bool paused);
		bool IsPaused() const;

	private:
		Scene();
		Scene(std::string& name);

	private:
		friend class SceneManager;

		bool m_isActiveScene = false;
		bool m_isPaused      = false;
		std::string m_sceneName;
		EntityManager m_entityRegistry;
	};

	template <typename TComponent, typename... TArgs>
	void Scene::AddComponent(Entity entity, TArgs&&... args)
	{
		m_entityRegistry.AddComponent<TComponent>(entity, std::forward<TArgs>(args)...);
	}

	template <typename TComponent>
	void Scene::RemoveComponent(Entity entity)
	{
		m_entityRegistry.RemoveComponent<TComponent>(entity);
	}

	template <typename TComponent>
	bool Scene::HasComponent(Entity entity) const
	{
		return m_entityRegistry.HasComponent<TComponent>(entity);
	}
} // namespace cedar
