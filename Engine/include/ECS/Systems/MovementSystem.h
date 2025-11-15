#pragma once

#include "ECS/Components/Components.h"
#include "Common/Input.h"
#include "Common/CedarTime.h"
namespace cedar
{
	class MovementSystem : public BaseSystem
	{
	public:
		DECL_TYPE_NAME(MovementSystem);

		MovementSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<RigidBodyComponent>();
		}

		virtual void FixedUpdate(float fixedDeltaTime) override
		{
			for (auto& entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
				auto rigidBody = entity.GetComponent<RigidBodyComponent>();

				// CEDAR_INFO("Entity id: {} has velocity: [x: {}, y: {}]", entity.GetId(), rigidBody->Velocity.x, rigidBody->Velocity.y);
				transform->Position.x += rigidBody->Velocity.x * static_cast<float>(fixedDeltaTime);
				transform->Position.y += rigidBody->Velocity.y * static_cast<float>(fixedDeltaTime);

				// CEDAR_INFO("entity with id: {} transform positions: x: {}, y: {}", entity.GetId(), transform->Position.x, transform->Position.y);
			}
		}
	};
} // namespace cedar
