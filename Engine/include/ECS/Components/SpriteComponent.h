#pragma once

#include <string>
#include <glm/glm.hpp>

namespace cedar
{
	struct SpriteComponent
	{
		std::string SpritePath;
		uint32_t Size;
		glm::vec2 Sise;

		SpriteComponent(std::string spritePath = "", uint32_t size = 0)
		{
			this->SpritePath = spritePath;
			this->Size = size;
		}
	};
} // namespace cedar
