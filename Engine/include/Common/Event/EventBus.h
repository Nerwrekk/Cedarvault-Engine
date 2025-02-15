#pragma once

#include "Events/IEvent.h"

#include <typeindex>
#include <vector>
#include <map>

namespace cedar
{
	class EventBus
	{
	public:
		EventBus();
		~EventBus();

		template <typename T>
		void SubscribeToEvent(void (*funcPtr)(IEvent*));

		template <typename T>
		void EmitEvent();

	private:
		std::map<std::type_index, std::vector<void (*)(IEvent*)>> m_subscibedCallbacks;
	};

	template <typename T>
	void EventBus::SubscribeToEvent(void (*funcPtr)(IEvent*))
	{
		m_subscibedCallbacks[std::type_index(typeid(T))].emplace(funcPtr);
	}

	template <typename T>
	void EventBus::EmitEvent()
	{
	}
} // namespace cedar