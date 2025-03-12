#pragma once

#include "ECS/Components/Components.h"
#include "ECS/ECS.h"

namespace cedar
{
	void SetEntityPosition(Entity entity, double x, double y)
	{
		auto transform = entity.GetComponent<TransformComponent>();
		transform->Position.x = x;
		transform->Position.y = y;
	}
} // namespace cedar
