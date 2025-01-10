#pragma once

#include "Common/SDL_Wrapper.h"
#include <glm/glm.hpp>

namespace cedar
{
	struct SpriteComponent
	{
		SDL_Texture* Texture;
		int Width;
		int Height;

		SpriteComponent(SDL_Texture* texture = nullptr, int width = 0, int height = 0)
		{
			this->Texture = texture;
			this->Width = width;
			this->Height = height;
		}
	};
} // namespace cedar
