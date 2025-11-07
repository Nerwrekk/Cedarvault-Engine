#pragma once

#include "Common/SDL_Wrapper.h"
#include "MeanScript/Primitives/MeanString.h"
#include "Common/Core.h"

#include <string>
#include <glm/glm.hpp>

namespace cedar
{
	struct CEDAR_API SpriteComponent
	{
		DECL_TYPE_NAME(SpriteComponent)

		int Width;
		int Height;
		uint32_t ZIndex;
		SDL_Rect SrcRect;
		Mean::MeanString TextureId;

		SpriteComponent(std::string textureId = "", int width = 0, int height = 0, uint32_t zIndex = 0, int srcRectX = 0, int srcRectY = 0)
		{
			this->TextureId = Mean::MeanString(textureId);
			this->Width     = width;
			this->Height    = height;
			this->ZIndex    = zIndex;
			this->SrcRect   = { srcRectX, srcRectY, width, height };
		}
	};

} // namespace cedar
