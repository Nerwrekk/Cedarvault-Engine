#pragma once

#include "ECS/ECS.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "BoxColliderComponent.h"
#include "ScriptComponent.h"
#include "CameraFollowComponent.h"
#include "IDComponent.h"

namespace constants
{
	inline extern const char* const RigidBodyComponent    = GET_NAME_LITERAL(RigidBodyComponent);
	inline extern const char* const SpriteComponent       = GET_NAME_LITERAL(SpriteComponent);
	inline extern const char* const AnimationComponent    = GET_NAME_LITERAL(AnimationComponent);
	inline extern const char* const BoxColliderComponent  = GET_NAME_LITERAL(BoxColliderComponent);
	inline extern const char* const ScriptComponent       = GET_NAME_LITERAL(ScriptComponent);
	inline extern const char* const CameraFollowComponent = GET_NAME_LITERAL(CameraFollowComponent);
}
