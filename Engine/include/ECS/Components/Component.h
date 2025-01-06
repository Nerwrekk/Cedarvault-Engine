#pragma once

#include "Common/Core.h"
#include <cstdint>

namespace cedar
{
	struct CEDAR_API IComponent
	{
		IComponent() = default;

	protected:
		static uint32_t s_nextId;
	};

	//NOTE when exporting this class using CEDAR_API, all sorts of linker errors showed up!
	template <typename T>
	class CEDAR_API Component : public IComponent
	{
	public:
		static uint32_t GetId()
		{
			//Static variable inside a function will keep its original value
			//this is why the GetId method works when using multiple components.
			static auto id = s_nextId++;

			return id;
		}
	};
} // namespace cedar
