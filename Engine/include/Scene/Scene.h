#pragma once

#include "Common/LayerStack.h"
#include "ECS/ECS.h"

namespace cedar
{
	class SceneManager;

	class Scene
	{
	public:
		Entity CreateEntity();
		void KillEntity(Entity entity);

		LayerStack* GetLayerStack();
		EntityManager* GetEntityRegister();

		void SetSceneName(std::string& name);
		std::string& GetSceneName();

		template <typename TComponent, typename... TArgs>
		void AddComponent(Entity entity, TArgs&&... args);

		template <typename TComponent>
		void RemoveComponent(Entity entity);

		template <typename TComponent>
		bool HasComponent(Entity entity) const;

		template <typename TLayer, typename... Args>
		TLayer* PushLayer(Args&&... args);

	private:
		Scene();
		Scene(std::string& name);

	private:
		friend class SceneManager;

		bool m_isActiveScene = false;
		std::string m_sceneName;
		LayerStack m_layerStack;
		EntityManager m_entityRegistry;
	};

	template <typename TLayer, typename... Args>
	TLayer* Scene::PushLayer(Args&&... args)
	{
		return m_layerStack.PushLayer<TLayer>(std::forward<Args>(args)...);
	}

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
