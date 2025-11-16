#pragma once

#include "Common/Constants.h"
namespace cedar
{
	namespace Time
	{
		inline float FixedDeltaTime = static_cast<float>(FIXED_DT);
		inline float DeltaTime      = 0.0f;
		inline float AlphaTime      = 0.0f;
	};
} // namespace cedar
