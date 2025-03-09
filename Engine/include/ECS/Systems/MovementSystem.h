#pragma once

#include "ECS/Components/Components.h"
#include "Common/Input.h"
#include "Common/Time.h"
namespace cedar
{
	class MovementSystem : public BaseSystem
	{
	public:
		MovementSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<RigidBodyComponent>();
		}

		virtual void Update() override
		{
			for (auto& entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
				auto rigidBody = entity.GetComponent<RigidBodyComponent>();

				transform->Position.x += rigidBody->Velocity.x * static_cast<float>(Time::DeltaTime);
				transform->Position.y += rigidBody->Velocity.y * static_cast<float>(Time::DeltaTime);

				// CEDAR_INFO("entity with id: {} transform positions: x: {}, y: {}", entity.GetId(), transform->Position.x, transform->Position.y);
			}
		}
	};
} // namespace cedar
