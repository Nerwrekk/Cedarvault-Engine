#pragma once

#include "IEvent.h"
#include "ECS/ECS.h"

namespace cedar
{
	struct CollisionExitEvent : public IEvent
	{
		DECL_TYPE_NAME(CollisionExitEvent);

		Entity First;
		Entity Second;

		CollisionExitEvent(Entity first, Entity second)
		    : First(first), Second(second) {};
	};
} // namespace cedar
