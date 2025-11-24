#include "Common/Event/EventBus.h"
#include "Application/Application.h"

namespace cedar
{
	EventBus* EventBus::s_EventBus = nullptr;
	EventBus::EventBus()
	{
		s_EventBus = this;
	}

	EventBus::~EventBus()
	{
	}

	EventBus* EventBus::Inst()
	{
		return s_EventBus;
	}

	void EventBus::PollEvents()
	{
		for (auto& [_, ptr] : m_eventRegistries)
		{
			auto registry = CastRegistry<uint8_t>(ptr);
			while (!registry->EventQueue.empty())
			{
				auto& event = reinterpret_cast<IEvent&>(*registry->EventQueue.front());
				Application::Get().RaiseEvent(event);
				if (!event.Handled)
				{
					for (auto& listener : registry->Listeners)
					{
						listener->Exectue(event);
					}
				}

				registry->EventQueue.pop();
			}
		}

		//frame callbacks
		while (!m_task.empty())
		{
			//Get first task function ptr and then call it directly!
			m_task.front()();
			m_task.pop();
		}
	}
}
// namespace cedar
