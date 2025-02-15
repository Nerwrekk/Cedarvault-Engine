#include "Common/Event/EventBus.h"

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
}
// namespace cedar
