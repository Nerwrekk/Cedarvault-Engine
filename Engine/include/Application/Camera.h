#pragma once

#include "Common/SDL_Wrapper.h"

namespace cedar
{
	struct Camera
	{
		float X = 0.f, Y = 0.f;         // current (float)
		float PrevX = 0.f, PrevY = 0.f; // previous (float)
		SDL_Rect Rect;
	};

} // namespace cedar
