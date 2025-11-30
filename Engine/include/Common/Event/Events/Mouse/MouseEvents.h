#pragma once

#include "Common/Event/Events/IEvent.h"

namespace cedar
{
	struct MouseReleaseEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseReleaseEvent);

		uint32_t Button;

		MouseReleaseEvent(uint32_t button)
		    : Button(button) {}
	};

	struct MouseDownEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseDownEvent);

		uint32_t Button;

		MouseDownEvent(uint32_t button)
		    : Button(button) {}
	};

	struct MouseDragEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseDragEvent);

		double DeltaX {};
		double DeltaY {};

		MouseDragEvent(double deltaX, double deltaY)
		    : DeltaX(deltaX), DeltaY(deltaY) {}
	};

	struct MouseMoveEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseMoveEvent);

		double TargetX {};
		double TargetY {};

		MouseMoveEvent(double x, double y)
		    : TargetX(x), TargetY(y) {}
	};

	struct MouseWheelEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseWheelEvent);

		double ScrollX {};
		double ScrollY {};

		MouseWheelEvent(double sx, double sy)
		    : ScrollX(sx), ScrollY(sy) {}
	};

}