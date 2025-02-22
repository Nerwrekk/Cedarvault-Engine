#include "IEvent.h"

namespace cedar
{
	struct KeyRepeatEvent : IEvent
	{
		KeyRepeatEvent(int key)
		    : Key(key) {}

		int Key = -1;
	};

	struct KeyPressEvent : IEvent
	{
		KeyPressEvent(int key)
		    : Key(key) {}

		int Key = -1;
	};

	struct KeyReleaseEvent : IEvent
	{
		KeyReleaseEvent(int key)
		    : Key(key) {}

		int Key = -1;
	};
} // namespace cedar
