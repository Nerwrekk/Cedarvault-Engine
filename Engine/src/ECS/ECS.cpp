#include "ECS/ECS.h"

#include "Common/Logger.h"

namespace cedar
{
	uint32_t Entity::GetId() const
	{
		return m_id;
	}

	//EntityManager
	EntityManager::EntityManager()
	{
	}

	void EntityManager::Initialize()
	{
		m_ComponentPools.reserve(32);
		m_entityComponentSignatures.reserve(32);
	}

	void EntityManager::Update()
	{
	}

	Entity EntityManager::CreateEntity()
	{
		int entityId = m_totalNumOfEntities++;
		if (entityId >= m_entityComponentSignatures.size())
		{
			m_entityComponentSignatures.resize(entityId + 1);
		}

		Entity entity(entityId);
		m_entitiesToBeAdded.insert(entity);

		CEDAR_INFO("Entity created with id: {}", entityId);
		return entity;
	}

	void EntityManager::KillEntity(Entity entity)
	{
	}

	EntityManager* EntityManager::s_EntityManager = nullptr;
	EntityManager* EntityManager::Instance()
	{
		if (s_EntityManager == nullptr)
		{
			s_EntityManager = new EntityManager();
		}

		return s_EntityManager;
	}

	void EntityManager::AddSystem()
	{
	}

	void EntityManager::RemoveSystem()
	{
	}

	void EntityManager::HasSystem()
	{
	}

	void EntityManager::GetSystem()
	{
	}

} // namespace cedar

namespace cedar
{
	void BaseSystem::AddEntityToSystem(Entity entity)
	{
		m_entities.push_back(entity);
	}

	void BaseSystem::RemoveEntityFromSystem(Entity entity)
	{
		m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [&entity](Entity otherEntity)
		{
			return entity.GetId() == otherEntity.GetId();
		}),
		    m_entities.end());
	}

	const std::vector<Entity>& BaseSystem::GetSystemEntities()
	{
		return m_entities;
	}

	const Signature& BaseSystem::GetComponentSignature()
	{
		return m_ComponentSignature;
	}
} // namespace cedar
