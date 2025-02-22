#pragma once

#include "Events/IEvent.h"
#include "EventCallback.h"

#include <typeindex>
#include <list>
#include <unordered_map>
#include <memory>
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

		template <typename TEvent, typename TOwner>
		void Subscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&));

		template <typename TEvent>
		void Subscribe(void (*freeCallbackFunction)(TEvent&));

		template <typename TEvent, typename TOwner>
		void Unsubscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&));

		template <typename TEvent>
		void Unsubscribe(void (*freeCallbackFunction)(TEvent&));

		template <typename TEvent>
		void EmitEvent(TEvent& event);

		template <typename TEvent>
		void EmitEvent(TEvent&& event);

	private:
		// std::unordered_map<std::type_index, std::list<std::function<void(IEvent*)>>> m_subscibedCallbacks;
		std::unordered_map<std::type_index, std::list<std::unique_ptr<IEventCallback>>> m_subscibedCallbacks;

		static EventBus* s_EventBus;
	};

	template <typename TEvent, typename TOwner>
	void EventBus::Subscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&))
	{
		m_subscibedCallbacks[typeid(TEvent)].push_back(std::make_unique<EventCallBack<TOwner, TEvent>>(owner, memberCallbackFunction));
	}

	template <typename TEvent>
	void EventBus::Subscribe(void (*freeCallbackFunction)(TEvent&))
	{
		m_subscibedCallbacks[typeid(TEvent)].push_back(std::make_unique<EventCallBack<EventBus, TEvent>>(freeCallbackFunction));
	}

	template <typename TEvent, typename TOwner>
	void EventBus::Unsubscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&))
	{
		auto& eventCallbacks = m_subscibedCallbacks[typeid(TEvent)];
		auto it = std::find_if(eventCallbacks.begin(), eventCallbacks.end(),
		    [&](std::unique_ptr<IEventCallback>& callback)
		{
			auto iEventCallback = callback.get();
			auto eventCallback = reinterpret_cast<EventCallBack<TOwner, TEvent>*>(iEventCallback);
			return eventCallback->GetMemberFunc() == memberCallbackFunction;
		});

		if (it != eventCallbacks.end())
		{
			eventCallbacks.erase(it); // Unique pointer gets destroyed here
		}
	}

	template <typename TEvent>
	void EventBus::Unsubscribe(void (*freeCallbackFunction)(TEvent&))
	{
		auto& eventCallbacks = m_subscibedCallbacks[typeid(TEvent)];
		auto it = std::find_if(eventCallbacks.begin(), eventCallbacks.end(),
		    [&](std::unique_ptr<IEventCallback>& callback)
		{
			auto iEventCallback = callback.get();
			auto eventCallback = reinterpret_cast<EventCallBack<EventBus, TEvent>*>(iEventCallback);
			return eventCallback->GetFreeFunc() == freeCallbackFunction;
		});

		if (it != eventCallbacks.end())
		{
			eventCallbacks.erase(it); // Unique pointer gets destroyed here
		}
	}

	template <typename TEvent>
	void EventBus::EmitEvent(TEvent& event)
	{
		auto& eventCallbacks = m_subscibedCallbacks[typeid(TEvent)];
		for (auto it = eventCallbacks.begin(); it != eventCallbacks.end(); it++)
		{
			auto handler = it->get();
			handler->Exectue(event);
		}
	}

	template <typename TEvent>
	void EventBus::EmitEvent(TEvent&& event)
	{
		auto& eventCallbacks = m_subscibedCallbacks[typeid(TEvent)];
		for (auto it = eventCallbacks.begin(); it != eventCallbacks.end(); it++)
		{
			auto handler = it->get();
			handler->Exectue(event);
		}
	}
} // namespace cedar