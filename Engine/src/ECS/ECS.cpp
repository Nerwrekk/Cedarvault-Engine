#include "ECS/ECS.h"

#include "Common/Logger.h"
#include "ECS/Components/Components.h"

namespace cedar
{
	Entity::Entity(uint32_t id)
	    : m_id(id) {};

	uint32_t Entity::GetId() const
	{
		return m_id;
	}

	void Entity::Kill()
	{
		if (m_manager)
		{
			m_manager->KillEntity(*this);
		}
	}

	EntityManager* EntityManager::s_EntityManager = nullptr;
	EntityManager::EntityManager()
	{
		m_ComponentPools.reserve(32);
		m_entityComponentSignatures.reserve(32);

		//TODO: add assert here!
		s_EntityManager = this;
	}

	void EntityManager::Update()
	{
		//Add new entities
		for (auto& entity : m_entitiesToBeAdded)
		{
			AddEntityToSystem(entity);
		}

		m_entitiesToBeAdded.clear();

		for (auto& entity : m_entitiesToBeRemoved)
		{
			RemoveEntityFromSystem(entity);

			//TODO: remove all components for said entity?
			// for (auto& component : m_ComponentPools)
			// {
			// 	auto t = component->[entity.GetId()];
			// }

			//reset component signatures for that entity
			m_entityComponentSignatures[entity.GetId()].reset();

			//add entity id to m_freeIds
			m_freeIds.push_back(entity.GetId());
		}

		m_entitiesToBeRemoved.clear();
	}

	Entity EntityManager::CreateEntity()
	{
		int entityId {};
		if (m_freeIds.empty())
		{
			entityId = m_totalNumOfEntities++;
			if (entityId >= m_entityComponentSignatures.size())
			{
				m_entityComponentSignatures.resize(entityId + 10);
			}
		}
		else
		{
			entityId = m_freeIds.front();
			m_freeIds.pop_front();
		}

		Entity entity(entityId);
		entity.m_manager = this;
		CEDAR_INFO("Entity created with id: {}", entityId);
		//All entities shall have transform components
		entity.AddComponent<TransformComponent>();

		m_entitiesToBeAdded.insert(entity);

		return entity;
	}

	void EntityManager::KillEntity(Entity entity)
	{
		m_entitiesToBeRemoved.emplace(entity);
	}

	void EntityManager::AddEntityToSystem(Entity entity)
	{
		const auto& entitySignature = m_entityComponentSignatures[entity.GetId()];
		for (auto [key, system] : m_systems)
		{
			auto systemComponentSignature = system->GetComponentSignature();
			if ((entitySignature & systemComponentSignature) == systemComponentSignature)
			{
				system->AddEntityToSystem(entity);
			}
		}
	}

	void EntityManager::RemoveEntityFromSystem(Entity entity)
	{
		for (auto [key, system] : m_systems)
		{
			system->RemoveEntityFromSystem(entity);
		}
	}

	EntityManager* EntityManager::Instance()
	{
		//TODO: Add assert here

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

	std::vector<Entity>& BaseSystem::GetSystemEntities()
	{
		return m_entities;
	}

	const Signature& BaseSystem::GetComponentSignature()
	{
		return m_ComponentSignature;
	}
} // namespace cedar
