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
		m_entities.reserve(200);
	}

	static uint32_t s_currentIdIndex = 0;
	Entity EntityManager::CreateEntity()
	{
		Entity entity(s_currentIdIndex);

		s_currentIdIndex++;
		m_entities.push_back(entity);

		return entity;
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
