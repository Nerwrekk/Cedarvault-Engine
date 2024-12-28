#pragma once

#include "ECS/Pool.h"

#include <vector>
#include <cstdint>
#include <bitset>

namespace cedar
{
	//Entity is just a simple container with an ID
	class Entity
	{
	public:
		Entity(uint32_t id)
		    : m_id(id) {};

		uint32_t GetId() const;

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
		void Initialize();
		Entity CreateEntity();
		static EntityManager* Instance();

	private:
		EntityManager();

		uint32_t m_totalNumOfEntities = 0;

		std::vector<Entitiy> m_entities;

		//Vector of component pools
		//Vector index = component type id
		//Pool index = entity id
		std::vector<IPool*> m_ComponentPools;

		static EntityManager* s_EntityManager;
	};
} // namespace cedar
