#pragma once

#include "Common/SDL_Wrapper.h"

#include <string>
#include <glm/glm.hpp>

namespace cedar
{
	struct SpriteComponent
	{
		std::string TextureId;
		int Width;
		int Height;
		uint32_t ZIndex;
		SDL_Rect SrcRect;

		SpriteComponent(std::string textureId = "", int width = 0, int height = 0, uint32_t zIndex = 0, int srcRectX = 0, int srcRectY = 0)
		{
			this->TextureId = textureId;
			this->Width = width;
			this->Height = height;
			this->ZIndex = zIndex;
			this->SrcRect = { srcRectX, srcRectY, width, height };
		}
	};
} // namespace cedar
