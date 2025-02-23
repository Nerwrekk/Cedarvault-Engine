#pragma once

#include "ECS/Components/Components.h"
#include "Common/Input.h"
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
			if (Input::IsKeyPressed(Key::A))
			{
				CEDAR_INFO("A is pressed");
			}

			if (Input::IsKeyReleased(Key::A))
			{
				CEDAR_INFO("A is released");
			}

			if (Input::IsKeyRepeated(Key::D))
			{
				CEDAR_INFO("D is repeadet");
			}

			for (auto& entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
				auto rigidBody = entity.GetComponent<RigidBodyComponent>();

				transform->Position.x += rigidBody->Velocity.x * static_cast<float>(deltaTime);
				transform->Position.y += rigidBody->Velocity.y * static_cast<float>(deltaTime);

				// CEDAR_INFO("entity with id: {} transform positions: x: {}, y: {}", entity.GetId(), transform->Position.x, transform->Position.y);
			}
		}
	};
} // namespace cedar
