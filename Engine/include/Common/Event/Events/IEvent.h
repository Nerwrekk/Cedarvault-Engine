#pragma once

#include "Common/Core.h"

namespace cedar
{
	//Wrapper for all events
	struct IEvent
	{
		bool Handled = false;
	};
} // namespace cedar
