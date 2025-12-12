#include "ECS/ECS.h"
#include "ECS/Systems/MovementSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/ScriptSystem.h"
#include "ECS/Systems/MeanScriptSystem.h"
#include "ECS/Systems/RenderBoxColliderSystem.h"
#include "ECS/Systems/CameraFollowSystem.h"
#include "ECS/Systems/RenderSystem.h"

#include "Common/Logger.h"
#include "Application/Application.h"
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

	EntityManager::EntityManager()
	{
		m_ComponentPools.reserve(32);
		m_entityComponentSignatures.reserve(32);
		m_allEntities.reserve(100);

		RegisterComponentType<RigidBodyComponent>(RigidBodyComponent::GetTypeName());
		RegisterComponentType<AnimationComponent>(AnimationComponent::GetTypeName());
		RegisterComponentType<BoxColliderComponent>(BoxColliderComponent::GetTypeName());
		RegisterComponentType<CameraFollowComponent>(CameraFollowComponent::GetTypeName());
		RegisterComponentType<ScriptComponent>(ScriptComponent::GetTypeName());
		RegisterComponentType<SpriteComponent>(SpriteComponent::GetTypeName());

		//TODO: Might be a temporary solution
		AddSystem<MeanScriptSystem>();
		AddSystem<MovementSystem>();
		AddSystem<CollisionSystem>();
		AddSystem<CameraFollowSystem>();
		AddSystem<AnimationSystem>();
		AddSystem<RenderBoxColliderSystem>();
		AddSystem<RenderSystem>();
	}

	EntityManager::~EntityManager()
	{
		for (auto pool : m_ComponentPools)
		{
			CEDAR_DELETE(pool);
		}

		m_ComponentPools.clear();
	}

	void EntityManager::Update()
	{
		//Add new entities
		for (auto& entity : m_entitiesToBeAdded)
		{
			AddEntityToSystem(entity);
			m_allEntities.push_back(entity);
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

			m_allEntities.erase(std::remove_if(m_allEntities.begin(), m_allEntities.end(), [&entity](Entity otherEntity)
			{
				return entity.GetId() == otherEntity.GetId();
			}),
			    m_allEntities.end());
		}

		m_entitiesToBeRemoved.clear();
	}

	Entity EntityManager::CreateEntity()
	{
		int entityId {};
		if (m_freeIds.empty())
		{
			entityId = m_totalNumOfEntityIds++;
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
		entity.AddComponent<IDComponent>();

		m_entitiesToBeAdded.insert(entity);

		return entity;
	}

	void EntityManager::KillEntity(Entity entity)
	{
		m_entitiesToBeRemoved.emplace(entity);
	}

	std::vector<Entity>& EntityManager::GetAllEntities()
	{
		return m_allEntities;
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

	void EntityManager::SnapshotPreviousState()
	{
		const auto componentId = TypeIdOf<TransformComponent>();
		if (componentId > m_ComponentPools.size() || m_ComponentPools[componentId] == nullptr)
		{
			return;
		}

		auto component = static_cast<Pool<TransformComponent>*>(m_ComponentPools[componentId]);
		for (int i = 0; i < component->Size(); i++)
		{
			auto& transform = component->Get(i);

			transform.PrevPosition = transform.Position;
			transform.PrevRotation = transform.Rotation;
		}

		// snapshot camera (assuming Application::Get().Camera() returns a reference)
		auto cam   = Application::Get().GetMainCamera();
		cam->PrevX = cam->X;
		cam->PrevY = cam->Y;
	}

} // namespace cedar

namespace cedar
{
	void BaseSystem::AddEntityToSystem(Entity entity)
	{
		if (std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end())
		{
			m_entities.push_back(entity);
		}
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
