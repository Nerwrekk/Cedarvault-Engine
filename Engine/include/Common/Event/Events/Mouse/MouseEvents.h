#pragma once

#include "IEvent.h"

namespace cedar
{
	//Mouse events
	struct MouseReleaseEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseReleaseEvent);

		MouseReleaseEvent(uint32_t button)
		    : Button(button) {}

		uint32_t Button = -1;
	};

	struct MouseDownEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseDownEvent);

		MouseDownEvent(uint32_t button)
		    : Button(button) {}

		uint32_t Button = -1;
	};

	struct MouseDragEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseDragEvent);

		MouseDragEvent(double deltaX, double deltaY)
		    : DeltaX(deltaX), DeltaY(deltaY) {}

		double DeltaX {};
		double DeltaY {};
	};

	struct MouseMoveEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseMoveEvent);

		MouseMoveEvent(double x, double y)
		    : TargetX(x), TargetY(y) {}

		double TargetX {};
		double TargetY {};
	};

	struct MouseWheelEvent : public IEvent
	{
		DECL_TYPE_NAME(MouseWheelEvent);

		MouseWheelEvent(double sx, double sy)
		    : ScrollX(sx), ScrollY(sy) {}

		double ScrollX {};
		double ScrollY {};
	};

}