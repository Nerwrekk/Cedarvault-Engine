#pragma once

#include "Common/Logger.h"

namespace cedar
{
	namespace Luie
	{
		class LuaBehaviour
		{
		public:
			LuaBehaviour() = default;

			void OnStart()
			{
				CEDAR_INFO("inside OnStart");
			}

			void OnUpdate()
			{
				CEDAR_INFO("inside OnStart");
			}
		};
	} // namespace Luie

} // namespace cedar
