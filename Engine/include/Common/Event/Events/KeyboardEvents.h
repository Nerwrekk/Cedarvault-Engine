#include "IEvent.h"

namespace cedar
{
	struct KeyRepeatEvent : IEvent
	{
		DECL_TYPE_NAME(KeyRepeatEvent);

		KeyRepeatEvent(int key)
		    : Key(key) {}

		int Key = -1;
	};

	struct KeyPressEvent : IEvent
	{
		DECL_TYPE_NAME(KeyPressEvent);

		KeyPressEvent(int key)
		    : Key(key) {}

		int Key = -1;
	};

	struct KeyReleaseEvent : IEvent
	{
		DECL_TYPE_NAME(KeyReleaseEvent);

		KeyReleaseEvent(int key)
		    : Key(key) {}

		int Key = -1;
	};
} // namespace cedar
