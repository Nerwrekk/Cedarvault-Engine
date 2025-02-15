#pragma once

#include "Events/IEvent.h"

#include <typeindex>
#include <list>
#include <unordered_map>
#include <type_traits>
#include <functional>

namespace cedar
{
	class EventBus
	{
	public:
		EventBus();
		~EventBus();

		static EventBus* Inst();

		template <typename TEvent>
		void SubscribeToEvent(void (*callback)(TEvent*));

		template <typename TEvent, typename TCallable, typename... TArgs>
		void Subscribe(TCallable&& callable, TArgs&&... args);

		template <typename TEvent>
		void EmitEvent(TEvent* event);

	private:
		std::unordered_map<std::type_index, std::list<std::function<void(IEvent*)>>> m_subscibedCallbacks;

		static EventBus* s_EventBus;
	};

	template <typename TEvent>
	void EventBus::SubscribeToEvent(void (*callback)(TEvent*))
	{
		m_subscibedCallbacks[std::type_index(typeid(TEvent))].push_back(reinterpret_cast<void*>(callback));
	}

	template <typename TEvent, typename TCallable, typename... TArgs>
	void EventBus::Subscribe(TCallable&& callable, TArgs&&... args)
	{
		std::function<void(TEvent*)> handler;

		if constexpr (std::is_member_function_pointer_v<std::decay_t<TCallable>>)
		{
			// Manually store the captured arguments before passing them to the lambda
			auto captured_args = std::make_tuple(std::forward<TArgs>(args)...);
			handler = [captured_args, method = std::forward<TCallable>(callable)](TEvent* event)
			{
				// Unpack the captured arguments inside the lambda (get the object to call method on)
				auto obj = std::get<0>(captured_args); // Assuming the first argument is the object
				(obj->*method)(event);                 // Call the member function
			};
		}
		else
		{
			// Handle normal function or lambda
			handler = std::forward<TCallable>(callable);
		}

		// Store the handler in the event map
		m_subscibedCallbacks[std::type_index(typeid(TEvent))].push_back([handler](IEvent* e) //using lambda here
		{
			handler(static_cast<TEvent*>(e)); // Correct casting of event
		});
	}

	template <typename TEvent>
	void EventBus::EmitEvent(TEvent* event)
	{
		auto eventCallbacks = m_subscibedCallbacks[std::type_index(typeid(TEvent))];
		for (auto& eventCallback : eventCallbacks)
		{
			eventCallback(event);
		}
	}
} // namespace cedar