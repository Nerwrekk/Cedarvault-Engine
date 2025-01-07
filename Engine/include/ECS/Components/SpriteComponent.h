#pragma once

#include <string>
#include <glm/glm.hpp>

namespace cedar
{
	struct SpriteComponent
	{
		std::string SpritePath;
		int Width;
		int Height;

		SpriteComponent(std::string spritePath = "", int width = 0, int height = 0)
		{
			this->SpritePath = spritePath;
			this->Width = width;
			this->Height = height;
		}
	};
} // namespace cedar
