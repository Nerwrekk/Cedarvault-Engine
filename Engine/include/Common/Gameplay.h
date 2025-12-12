#pragma once

#include <string>
#include "MeanScript/Primitives/MeanString.h"

namespace cedar
{
	struct Sprite
	{
		int Width;
		int Height;
		SDL_Rect SrcRect {};
		SDL_Texture* Texture;
		Mean::MeanString Name;

		Sprite() = default;
	};

} // namespace cedar
