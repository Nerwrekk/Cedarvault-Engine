#pragma once

#include "IEvent.h"

namespace cedar
{
	//Window events
	struct WindowMaximizeEvent : IEvent
	{
		DECL_TYPE_NAME(WindowMaximizeEvent);
	};

	struct WindowIconifyEvent : IEvent
	{
		DECL_TYPE_NAME(WindowIconifyEvent);
	};

	struct WindowRestoreEvent : IEvent
	{
		DECL_TYPE_NAME(WindowRestoreEvent);
	};

	struct WindowCloseEvent : IEvent
	{
		DECL_TYPE_NAME(WindowCloseEvent);
	};

	struct WindowResizeEvent : IEvent
	{
		WindowResizeEvent(int w, int h)
		    : Width(w), Height(h) {}

		int Width {};
		int Height {};

		DECL_TYPE_NAME(WindowResizeEvent);
	};
}