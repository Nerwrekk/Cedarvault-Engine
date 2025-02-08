#pragma once

#include "Common/Core.h"

#include <glm/glm.hpp>

namespace cedar
{
	struct CEDAR_API BoxColliderComponent
	{
		int Width;
		int Height;
		glm::vec2 Offset;

		BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0))
		{
			this->Width = width;
			this->Height = height;
			this->Offset = offset;
		}
	};
} // namespace cedar
