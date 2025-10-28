#pragma once

#include "IEvent.h"
#include "ECS/ECS.h"

namespace cedar
{
	struct CollisionEvent : public IEvent
	{
		DECL_TYPE_NAME(CollisionEvent);

		Entity First;
		Entity Second;

		CollisionEvent(Entity first, Entity second)
		    : First(first), Second(second) {};
	};
} // namespace cedar
