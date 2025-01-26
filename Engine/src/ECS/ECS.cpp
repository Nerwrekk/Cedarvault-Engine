#include "ECS/ECS.h"

#include "Common/Logger.h"
#include "ECS/Components/Components.h"

namespace cedar
{
	uint32_t Entity::GetId() const
	{
		return m_id;
	}

	EntityManager* EntityManager::s_EntityManager = nullptr;
	EntityManager::EntityManager()
	{
		m_ComponentPools.reserve(32);
		m_entityComponentSignatures.reserve(32);

		//TODO: add assert here!
		s_EntityManager = this;

		RegisterComponents();
	}

	void EntityManager::Update()
	{
		//Add new entities
		for (auto& entity : m_entitiesToBeAdded)
		{
			AddEntityToSystem(entity);
		}

		m_entitiesToBeAdded.clear();
	}

	Entity EntityManager::CreateEntity()
	{
		int entityId = m_totalNumOfEntities++;
		if (entityId >= m_entityComponentSignatures.size())
		{
			m_entityComponentSignatures.resize(entityId + 10);
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

	//NOTE! we need to pre register all compoents in the engine otherwise the game project
	//will get an error LNK2019: unresolved external symbol error
	void EntityManager::RegisterComponents()
	{
		Component<TransformComponent>::GetId();
		Component<RigidBodyComponent>::GetId();
		Component<SpriteComponent>::GetId();
		Component<AnimationComponent>::GetId();
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
