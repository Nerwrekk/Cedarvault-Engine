#pragma once

#include "Events/IEvent.h"
#include "EventCallback.h"
#include "EventRegistry.h"
#include "CedarAssert.h"

#include <typeindex>
#include <list>
#include <map>
#include <memory>
#include <type_traits>
#include <functional>
#include <queue>

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

		// template <typename TEvent>
		// void EventBus::PostEvent(TEvent& event);

		// template <typename TEvent>
		// void EventBus::PostEvent(TEvent&& event);

		template <typename TEvent, typename... Args>
		void PostEvent(Args&&... args);

		template <typename Task>
		void PostTask(Task&& task);

		template <typename TEvent>
		void EmitEvent(TEvent& event);

		template <typename TEvent>
		void EmitEvent(TEvent&& event);

		template <typename Event>
		EventRegistry<Event>* GetRegistry();

		template <typename Event>
		EventRegistry<Event>* CastRegistry(void* ptr);

		void PollEvents();

	private:
		std::map<uint32_t, void*> m_eventRegistries;
		std::queue<std::function<void()>> m_task;

		static EventBus* s_EventBus;
	};

	//tries to find the registry based on the event thats passed in the template
	template <typename Event>
	EventRegistry<Event>* EventBus::GetRegistry()
	{
		CEDAR_STATIC_ASSERT(std::is_base_of<IEvent, Event>::value);

		auto eventID = TypeIdOf<Event>();
		//check if EventRegistry already exists
		auto it = m_eventRegistries.find(eventID);
		if (it != m_eventRegistries.end())
		{
			return CastRegistry<Event>(it->second);
		}

		//It does not exist so we create a new one and return it
		auto registry              = new EventRegistry<Event>();
		m_eventRegistries[eventID] = registry;

		return registry;
	}

	template <typename Event>
	EventRegistry<Event>* EventBus::CastRegistry(void* ptr)
	{
		return static_cast<EventRegistry<Event>*>(ptr);
	}

	template <typename TEvent, typename TOwner>
	void EventBus::Subscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&))
	{
		EventRegistry<TEvent>* registry = GetRegistry<TEvent>();
		registry->Listeners.push_back(std::make_unique<EventCallBack<TOwner, TEvent>>(owner, memberCallbackFunction));
	}

	template <typename TEvent>
	void EventBus::Subscribe(void (*freeCallbackFunction)(TEvent&))
	{
		EventRegistry<TEvent>* registry = GetRegistry<TEvent>();
		registry->Listeners.push_back(std::make_unique<EventCallBack<EventBus, TEvent>>(freeCallbackFunction));
	}

	template <typename TEvent, typename TOwner>
	void EventBus::Unsubscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&))
	{
		EventRegistry<TEvent>* registry = GetRegistry<TEvent>();

		auto it = std::find_if(registry->Listeners.begin(), registry->Listeners.end(),
		    [&](std::unique_ptr<IEventCallback>& callback)
		{
			auto iEventCallback = callback.get();
			auto eventCallback  = reinterpret_cast<EventCallBack<TOwner, TEvent>*>(iEventCallback);

			return eventCallback->GetMemberFunc() == memberCallbackFunction;
		});

		if (it != registry->Listeners.end())
		{
			registry->Listeners.erase(it); // Unique pointer gets destroyed here
		}
	}

	template <typename TEvent>
	void EventBus::Unsubscribe(void (*freeCallbackFunction)(TEvent&))
	{
		EventRegistry<TEvent>* registry = GetRegistry<TEvent>();

		auto it = std::find_if(registry->Listeners.begin(), registry->Listeners.end(),
		    [&](std::unique_ptr<IEventCallback>& callback)
		{
			auto iEventCallback = callback.get();
			auto eventCallback  = reinterpret_cast<EventCallBack<EventBus, TEvent>*>(iEventCallback);

			return eventCallback->GetFreeFunc() == freeCallbackFunction;
		});

		if (it != registry->Listeners.end())
		{
			registry->Listeners.erase(it); // Unique pointer gets destroyed here
		}
	}

	template <typename TEvent, typename... Args>
	void EventBus::PostEvent(Args&&... args)
	{
		EventRegistry<TEvent>* registry = GetRegistry<TEvent>();
		if (registry->Listeners.empty())
		{
			return;
		}

		registry->EventQueue.push(std::make_unique<TEvent>(std::forward<Args>(args)...));
	}

	//Task is a lambda function
	template <typename Task>
	void EventBus::PostTask(Task&& task)
	{
		m_task.push(std::move(task));
	}

	template <typename TEvent>
	void EventBus::EmitEvent(TEvent& event)
	{
		EventRegistry<TEvent>* registry = GetRegistry<TEvent>();
		for (auto it = registry->Listeners.begin(); it != registry->Listeners.end(); it++)
		{
			auto handler = it->get();
			handler->Exectue(event);
		}
	}

	template <typename TEvent>
	void EventBus::EmitEvent(TEvent&& event)
	{
		EventRegistry<TEvent>* registry = GetRegistry<TEvent>();
		for (auto it = registry->Listeners.begin(); it != registry->Listeners.end(); it++)
		{
			auto handler = it->get();
			handler->Exectue(event);
		}
	}
} // namespace cedar