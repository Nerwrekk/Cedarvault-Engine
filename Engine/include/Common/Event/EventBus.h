#pragma once

#include "Events/IEvent.h"

#include <typeindex>
#include <vector>
#include <unordered_map>

namespace cedar
{
	class EventBus
	{
	public:
		EventBus();
		~EventBus();

		template <typename TEvent>
		void SubscribeToEvent(void (*callback)(TEvent*));

		template <typename TEvent>
		void EmitEvent(TEvent* event);

	private:
		std::unordered_map<std::type_index, std::vector<void*>> m_subscibedCallbacks;
	};

	template <typename TEvent>
	void EventBus::SubscribeToEvent(void (*callback)(TEvent*))
	{
		m_subscibedCallbacks[std::type_index(typeid(TEvent))].push_back(reinterpret_cast<void*>(callback));
	}

	template <typename TEvent>
	void EventBus::EmitEvent(TEvent* event)
	{
		auto eventCallbacks = m_subscibedCallbacks[std::type_index(typeid(TEvent))];
		for (auto& eventCallback : eventCallbacks)
		{
			auto callback = reinterpret_cast<void (*)(TEvent*)>(eventCallback);
			callback(event);
		}
	}
} // namespace cedar