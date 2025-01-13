#pragma once

#include <string>
#include <glm/glm.hpp>

namespace cedar
{
	struct SpriteComponent
	{
		std::string TextureId;
		int Width;
		int Height;

		SpriteComponent(std::string textureId = "", int width = 0, int height = 0)
		{
			this->TextureId = textureId;
			this->Width = width;
			this->Height = height;
		}
	};
} // namespace cedar
