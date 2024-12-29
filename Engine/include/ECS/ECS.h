#pragma once

#include "ECS/Pool.h"

#include <vector>
#include <cstdint>
#include <bitset>
#include <typeindex>
#include <unordered_map>
#include <set>

namespace cedar
{
	//Entity is just a simple container with an ID
	class Entity
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

	private:
		uint32_t m_id;
	};

	struct IComponent
	{
	protected:
		inline static uint32_t s_nextId = 0;
	};

	template <typename T>
	class Component : public IComponent
	{
	public:
		static uint32_t GetId()
		{
			//Static variable inside a function will keep its original value
			//this is why the GetId method works when using multiple components.
			static uint32_t id = s_nextId++;

			return id;
		}
	};

	const uint32_t MAX_COMPONENTS = 32;
	//Bitset to keep track of which components are active for the current Entity
	typedef std::bitset<MAX_COMPONENTS> Signature;
	class BaseSystem
	{
	public:
		BaseSystem() = default;
		~BaseSystem() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem(Entity entity);
		const std::vector<Entity>& GetSystemEntities();
		const Signature& GetComponentSignature();

		template <typename T>
		void RequireComponent()
		{
			const auto componentId = Component<T>::GetId();
			m_ComponentSignature.set(componentId);
		}

	protected:
		virtual void Update() {};

	protected:
		Signature m_ComponentSignature;
		std::vector<Entity> m_entities;
	};

	class EntityManager
	{
	public:
		static EntityManager* Instance();

		void Initialize();
		void Update();

		Entity CreateEntity();
		void KillEntity(Entity entity);

		template <typename TComponent, typename... Args>
		void AddComponent(Entity entity, Args&&... args)
		{
			const auto componentId = Component<TComponent>::GetId();
			const auto entityId = entity.GetId();

			if (componentId >= m_ComponentPools.size())
			{
				m_ComponentPools.resize(componentId + 10, nullptr);
			}

			//If we don't have a pool yet for this component type
			if (!m_ComponentPools[componentId])
			{
				Pool<TComponent>* newComponentPool = new Pool<TComponent>();
				m_ComponentPools[componentId] = newComponentPool;
			}

			Pool<TComponent>* componentPool = reinterpret_cast<Pool<TComponent>*>(m_ComponentPools[componentId]);
			if (m_totalNumOfEntities >= componentPool->Size())
			{
				componentPool->Resize(m_totalNumOfEntities);
			}

			TComponent component = TComponent(std::forward<Args>(args)...);
			componentPool->Set(entityId, component);

			m_entityComponentSignatures[entityId].set(componentId);
		}

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
		}

		template <typename TComponent>
		TComponent& GetComponent(Entity entity);

		void AddSystem();
		void RemoveSystem();
		void HasSystem();
		void GetSystem();

	private:
		EntityManager();
		std::set<Entity> m_entitiesToBeAdded;
		std::set<Entity> m_entitiesToBeRemoved;

		uint32_t m_totalNumOfEntities = 0;

		//Vector of component pools
		//Vector index == component type id
		//Pool index == entity id
		std::vector<IPool*> m_ComponentPools;

		//Vector of component signatures per entity, saying which component is turned of for that entity
		//Vector index == entity id
		std::vector<Signature> m_entityComponentSignatures;

		std::unordered_map<std::type_index, BaseSystem*> m_Systems;

		static EntityManager* s_EntityManager;
	};
} // namespace cedar
