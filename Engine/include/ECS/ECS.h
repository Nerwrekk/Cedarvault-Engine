#pragma once

#include "Common/Core.h"
#include "ECS/Components/Component.h"
#include "ECS/Pool.h"
#include "Common/Logger.h"

#include <vector>
#include <cstdint>
#include <bitset>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <set>
#include <deque>

namespace cedar
{
	//Entity is just a simple container with an ID
	class CEDAR_API Entity
	{
	public:
		Entity(uint32_t id)
		    : m_id(id) {};

		uint32_t GetId() const;

		bool operator==(const Entity& other) const
		{
			return m_id == other.m_id;
		}

		bool operator<(const Entity& other) const
		{
			return m_id < other.m_id;
		}

		bool operator>(const Entity& other) const
		{
			return m_id > other.m_id;
		}

		void Kill();

		template <typename TComponent, typename... Args>
		void AddComponent(Args&&... args)
		{
			if (m_manager)
			{
				m_manager->AddComponent<TComponent>(*this, std::forward<Args>(args)...);
			}
		}

		template <typename TComponent>
		TComponent* GetComponent() const
		{
			if (m_manager)
			{
				return m_manager->GetComponent<TComponent>(*this);
			}

			return nullptr;
		}

		template <typename TComponent>
		void RemoveComponent()
		{
			if (m_manager)
			{
				m_manager->RemoveComponent<TComponent>(*this);
			}
		}

		template <typename TComponent>
		bool HasComponent() const
		{
			if (m_manager)
			{
				return m_manager->HasComponent<TComponent>(*this);
			}

			return false;
		}

	private:
		friend class EntityManager;

		uint32_t m_id;
		EntityManager* m_manager;
	};

	const uint32_t MAX_COMPONENTS = 32;
	//Bitset to keep track of which components are active for the current Entity
	typedef std::bitset<MAX_COMPONENTS> Signature;
	class BaseSystem
	{
	public:
		BaseSystem()
		{
			m_entities.reserve(100);
		}
		virtual ~BaseSystem() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem(Entity entity);
		std::vector<Entity>& GetSystemEntities();
		const Signature& GetComponentSignature();

		template <typename T>
		void RequireComponent()
		{
			const auto componentId = Component<T>::GetId();
			m_ComponentSignature.set(componentId);
		}

		virtual void Update(double deltaTime) {};

	protected:
		Signature m_ComponentSignature;
		std::vector<Entity> m_entities;
	};

	class CEDAR_API EntityManager
	{
	public:
		static EntityManager* Instance();

		EntityManager();
		void Update();

		Entity CreateEntity();
		void KillEntity(Entity entity);
		void AddEntityToSystem(Entity entity);

		template <typename TComponent, typename... Args>
		void AddComponent(Entity entity, Args&&... args);

		template <typename TComponent>
		void RemoveComponent(Entity entity)
		{
			const auto componentId = Component<TComponent>::GetId();
			const auto entityId = entity.GetId();

			m_entityComponentSignatures[entityId].set(componentId, false);
		}

		template <typename TComponent>
		bool HasComponent(Entity entity) const
		{
			const auto componentId = Component<TComponent>::GetId();
			const auto entityId = entity.GetId();

			return m_entityComponentSignatures[entityId].test(componentId);
		}

		template <typename TComponent>
		TComponent* GetComponent(Entity entity) const
		{
			const auto componentId = Component<TComponent>::GetId();
			const auto entityId = entity.GetId();
			if (HasComponent<TComponent>(entity))
			{
				auto component = std::static_pointer_cast<Pool<TComponent>>(m_ComponentPools[componentId]);

				return &component->Get(entityId);
			}

			return nullptr;
		}

		template <typename TSystem, typename... TArgs>
		void AddSystem(TArgs&&... args)
		{
			auto system = m_systems.find(std::type_index(typeid(TSystem)));
			if (system != m_systems.end())
			{
				//System already added so we can return
				//TODO: make assert here, we should not have multiple of the same system
				return;
			}
			else
			{
				auto newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
				m_systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
			}
		}

		template <typename TSystem>
		void RemoveSystem()
		{
			auto system = m_systems.find(std::type_index(typeid(TSystem)));
			if (system != m_systems.end())
			{
				m_systems.erase(system);
			}
		}

		template <typename TSystem>
		void HasSystem() const
		{
			auto system = m_systems.find(std::type_index(typeid(TSystem)));
			system != m_systems.end() ? return true : return false;
		}

		template <typename TSystem>
		std::shared_ptr<TSystem> GetSystem() const
		{
			auto system = m_systems.find(std::type_index(typeid(TSystem)));
			if (system != m_systems.end())
			{
				return std::static_pointer_cast<TSystem>(system->second);
			}

			return nullptr;
		}

		void UpdateAllSystems(double deltaTime)
		{
			for (auto& [key, system] : m_systems)
			{
				system->Update(deltaTime);
			}
		}

		void RemoveEntityFromSystem(Entity entity);

	private:
		std::set<Entity> m_entitiesToBeAdded;
		std::set<Entity> m_entitiesToBeRemoved;
		std::deque<int> m_freeIds;

		uint32_t m_totalNumOfEntities = 0;

		//Vector of component pools
		//Vector index == component type id
		//Pool index == entity id
		std::vector<std::shared_ptr<IPool>> m_ComponentPools;

		//Vector of component signatures per entity, saying which component is turned of for that entity
		//Vector index == entity id
		std::vector<Signature> m_entityComponentSignatures;

		std::unordered_map<std::type_index, std::shared_ptr<BaseSystem>> m_systems;

		static EntityManager* s_EntityManager;
	};

	template <typename TComponent, typename... Args>
	void EntityManager::AddComponent(Entity entity, Args&&... args)
	{
		auto componentId = Component<TComponent>::GetId();
		const auto entityId = entity.GetId();

		if (componentId >= m_ComponentPools.size())
		{
			m_ComponentPools.resize(componentId + 10, nullptr);
		}

		//If we don't have a pool yet for this component type
		if (!m_ComponentPools[componentId])
		{
			auto newComponentPool = std::make_shared<Pool<TComponent>>();
			m_ComponentPools[componentId] = newComponentPool;
		}

		auto componentPool = std::static_pointer_cast<Pool<TComponent>>(m_ComponentPools[componentId]);
		if (m_totalNumOfEntities >= componentPool->Size())
		{
			componentPool->Resize(m_totalNumOfEntities);
		}

		TComponent component = TComponent(std::forward<Args>(args)...);
		componentPool->Set(entityId, component);

		m_entityComponentSignatures[entityId].set(componentId);

		CEDAR_INFO("Component with id: {} was added to entity with id: {}", componentId, entityId);
	}
} // namespace cedar
