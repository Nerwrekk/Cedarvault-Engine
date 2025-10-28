#pragma once

#include "common/Core.h"
#include "EventCallback.h"

#include <queue>

namespace cedar
{
	//Manages listeners and has an event-queue for a particular type of event
	template <typename TEvent>
	class EventRegistry
	{
	public:
		using Listener = std::unique_ptr<IEventCallback>;
		EventRegistry()
		{
			Listeners.reserve(10);
		}
		std::queue<std::unique_ptr<TEvent>> EventQueue;
		std::vector<Listener> Listeners;
	};
}