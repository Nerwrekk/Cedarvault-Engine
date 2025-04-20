#pragma once

#include "ECS/Components/Components.h"
#include "ECS/ECS.h"
#include "Common/Input.h"
#include "Common/KeyCodes.h"

#include <tuple>
#include <glm/glm.hpp>

namespace Mean
{
	using SetEntityPosition_fn = void (*)(cedar::Entity, double, double);
	using GetTranformComponent_fn = void* (*)(cedar::Entity);

	//Keyboard functions:
	using IsKeyPressed_fn = bool (*)(const cedar::KeyCode);

	struct MeanNativeBindings
	{
		SetEntityPosition_fn SetEntityPositionFn;
		GetTranformComponent_fn GetTranformComponentFn;
		IsKeyPressed_fn IsKeyPressedFn;
	};

	extern "C"
	{
		void SetEntityPosition(cedar::Entity entity, double x, double y)
		{
			auto transform = entity.GetComponent<cedar::TransformComponent>();
			transform->Position.x = x;
			transform->Position.y = y;
		}

		void* GetTransformComponent(cedar::Entity entity)
		{
			return static_cast<void*>(entity.GetComponent<cedar::TransformComponent>());
		}
	}

	// std::tuple<double, double> GetEntityPosition(Entity entity)
	// {
	// 	auto transform = entity.GetComponent<TransformComponent>();

	// 	return std::make_tuple(transform->Position.x, transform->Position.y);
	// }

	// void SetEntityVelocity(Entity entity, double x, double y)
	// {
	// 	auto ridigbody = entity.GetComponent<RigidBodyComponent>();
	// 	ridigbody->Velocity.x = x;
	// 	ridigbody->Velocity.y = y;
	// }

	// std::tuple<double, double> GetEntityVelocity(Entity entity)
	// {
	// 	auto ridigbody = entity.GetComponent<RigidBodyComponent>();

	// 	return std::make_tuple(ridigbody->Velocity.x, ridigbody->Velocity.y);
	// }

	// SpriteComponent* GetSpriteComponent(Entity entity)
	// {
	// 	return entity.GetComponent<SpriteComponent>();
	// }

	// TransformComponent* GetTransformComponent(Entity entity)
	// {
	// 	return entity.GetComponent<TransformComponent>();
	// }
} // namespace Mean
