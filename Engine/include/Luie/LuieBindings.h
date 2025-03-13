#pragma once

#include "ECS/Components/Components.h"
#include "ECS/ECS.h"
#include "Common/Input.h"
#include "Common/KeyCodes.h"

#include <sol/sol.hpp>
#include <tuple>
namespace cedar
{
	void SetEntityPosition(Entity entity, double x, double y)
	{
		auto transform = entity.GetComponent<TransformComponent>();
		transform->Position.x = x;
		transform->Position.y = y;
	}

	std::tuple<double, double> GetEntityPosition(Entity entity)
	{
		auto transform = entity.GetComponent<TransformComponent>();

		return std::make_tuple(transform->Position.x, transform->Position.y);
	}

	void SetEntityVelocity(Entity entity, double x, double y)
	{
		auto ridigbody = entity.GetComponent<RigidBodyComponent>();
		ridigbody->Velocity.x = x;
		ridigbody->Velocity.y = y;
	}

	std::tuple<double, double> GetEntityVelocity(Entity entity)
	{
		auto ridigbody = entity.GetComponent<RigidBodyComponent>();

		return std::make_tuple(ridigbody->Velocity.x, ridigbody->Velocity.y);
	}

	void SetLuieBindings(sol::state& lua)
	{
		lua.set_function("SetPosition", SetEntityPosition);
		lua.set_function("GetPosition", GetEntityPosition);
		lua.set_function("SetVelocity", SetEntityVelocity);
		lua.set_function("GetVelocity", GetEntityVelocity);

		//Keyboard functions
		lua.set_function("IsKeyPressed", &Input::IsKeyPressed);
		lua.set_function("IsKeyRepeated", &Input::IsKeyRepeated);
		lua.set_function("IsKeyReleased", &Input::IsKeyReleased);

		// Bind KeyCodes
		sol::table keys = lua.create_table();
		keys["A"] = Key::A;
		keys["D"] = Key::D;
		keys["W"] = Key::W;
		keys["S"] = Key::S;

		lua["Keys"] = keys;
	}
} // namespace cedar
