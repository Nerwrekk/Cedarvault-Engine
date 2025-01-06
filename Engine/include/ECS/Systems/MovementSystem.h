#pragma once

#include "ECS/Components/Components.h"

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

		virtual void Update(double deltaTime) override
		{
			for (auto& entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
				auto rigidBody = entity.GetComponent<RigidBodyComponent>();

				transform->Position.x += rigidBody->Velocity.x * deltaTime;
				transform->Position.y += rigidBody->Velocity.y * deltaTime;

				CEDAR_INFO("entity with id: {} transform positions: x: {}, y: {}", entity.GetId(), transform->Position.x, transform->Position.y);
			}
		}
	};
} // namespace cedar
