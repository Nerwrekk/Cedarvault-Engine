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
		static uint32_t s_nextId;
	};

	template <typename T>
	class Component : public IComponent
	{
	public:
		static uint32_t GetId()
		{
			static auto id = s_nextId++;

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

		void AddComponent(Entity entity);
		void RemoveComponent(Entity entity);
		void HasComponent(Entity entity);

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
