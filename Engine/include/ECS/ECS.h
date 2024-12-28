#pragma once

#include <vector>
#include <cstdint>
#include <bitset>

namespace cedar
{
	class Entity
	{
	public:
		Entity(uint32_t id)
		    : m_id(id) {};

		uint32_t GetId() const;

	private:
		uint32_t m_id;
	};

	class BaseComponent
	{
	private:
		uint32_t m_id;
	};

	const uint32_t MAX_COMPONENTS = 32;
	//Bitset to keep track of which components are active for the current Entity
	typedef std::bitset<MAX_COMPONENTS> Signature;
	class BaseSystem
	{
	public:
		BaseSystem() = default;
		~BaseSystem() = default;

		void AddEntityToSystem(Entity* entity);
		void RemoveEntityToSystem(Entity* entity);
		std::vector<Entity*> GetSystemEntities() const;
		Signature& GetComponentSignature() const;

	protected:
		virtual void Update() {};

	protected:
		Signature m_ComponentSignature;
		std::vector<Entity*> m_entities;
	};

	class EntityManager
	{
	public:
		void Initialize();
		Entity* CreateEntity();
		static EntityManager* Instance();

	private:
		EntityManager();

		std::vector<Entity*> m_entities;

		static EntityManager* s_EntityManager;
	};
} // namespace cedar
