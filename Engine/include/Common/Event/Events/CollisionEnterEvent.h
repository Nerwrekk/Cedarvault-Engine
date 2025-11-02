#pragma once

#include "IEvent.h"
#include "ECS/ECS.h"

namespace cedar
{
	struct CollisionEnterEvent : public IEvent
	{
		DECL_TYPE_NAME(CollisionEnterEvent);

		Entity First;
		Entity Second;

		CollisionEnterEvent(Entity first, Entity second)
		    : First(first), Second(second) {};
	};
} // namespace cedar
