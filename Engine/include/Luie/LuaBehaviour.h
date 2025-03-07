#pragma once

#include "Common/Logger.h"

#include <sol/sol.hpp>

namespace cedar
{
	namespace Luie
	{
		class LuaBehaviour
		{
		public:
			LuaBehaviour()
			{
				sol::metatable();
			};

			void OnStart()
			{
				CEDAR_INFO("inside OnStart from c++");
			}

			void OnUpdate()
			{
				CEDAR_INFO("inside OnUpdate c++");
			}
		};
	} // namespace Luie

} // namespace cedar
