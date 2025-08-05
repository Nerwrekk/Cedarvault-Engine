#pragma once

#include "ECS/ECS.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "BoxColliderComponent.h"
#include "ScriptComponent.h"
#include "CameraFollowComponent.h"

namespace constants
{
	inline extern const char* const RigidBodyComponent = "RigidbodyComponent";
	inline extern const char* const SpriteComponent = "SpriteComponent";
	inline extern const char* const AnimationComponent = "AnimationComponent";
	inline extern const char* const BoxColliderComponent = "BoxColliderComponent";
	inline extern const char* const ScriptComponent = "ScriptComponent";
	inline extern const char* const CameraFollowComponent = "CameraFollowComponent";
}
