#pragma once

#include "ECS/Components/Components.h"
#include "ECS/ECS.h"
#include "Common/Input.h"
#include "Common/KeyCodes.h"

#include <sol/sol.hpp>
#include <tuple>
#include <glm/glm.hpp>

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

	SpriteComponent* GetSpriteComponent(Entity entity)
	{
		return entity.GetComponent<SpriteComponent>();
	}

	TransformComponent* GetTransformComponent(Entity entity)
	{
		return entity.GetComponent<TransformComponent>();
	}

	void SetLuieBindings(sol::state& lua)
	{
		lua.new_usertype<glm::vec2>("vec2",
		    "x", &glm::vec2::x,
		    "y", &glm::vec2::y);

		lua.new_usertype<SDL_Rect>("sdl_rect",
		    "x", &SDL_Rect::x,
		    "y", &SDL_Rect::y,
		    "w", &SDL_Rect::w,
		    "h", &SDL_Rect::h);

		//Components
		lua.new_usertype<TransformComponent>("transform",
		    "position", &TransformComponent::Position,
		    "scale", &TransformComponent::Scale,
		    "rotation", &TransformComponent::Rotation);

		lua.new_usertype<SpriteComponent>("SpriteComponent",
		    "Sprite", &SpriteComponent::TextureId,
		    "Width", &SpriteComponent::Width,
		    "Height", &SpriteComponent::Height,
		    "ZIndex", &SpriteComponent::ZIndex,
		    "SrcRect", &SpriteComponent::SrcRect);

		lua.set_function("GetSpriteComponent", &GetSpriteComponent);
		lua.set_function("GetTransformComponent", &GetTransformComponent);

		//Utility functions
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
		keys["Space"] = Key::Space;

		lua["Keys"] = keys;
	}
} // namespace cedar
