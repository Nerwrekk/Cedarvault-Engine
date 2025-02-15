#pragma once

#include "IEvent.h"
#include "ECS/ECS.h"

namespace cedar
{
	struct CollisionEvent : public IEvent
	{
		Entity First;
		Entity Second;

		CollisionEvent(Entity first, Entity second)
		    : First(First), Second(second) {};
	};
} // namespace cedar
