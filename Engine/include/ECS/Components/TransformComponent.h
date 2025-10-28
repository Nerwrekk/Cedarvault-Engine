#pragma once

#include "Common/Core.h"

#include <glm/glm.hpp>

namespace cedar
{
	struct TransformComponent
	{
		DECL_TYPE_NAME(TransformComponent)

		glm::vec2 Position;
		glm::vec2 Scale;
		double Rotation;

		TransformComponent(glm::vec2 position = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1), double rotation = 0)
		{
			this->Position = position;
			this->Scale    = scale;
			this->Rotation = rotation;
		};
	};
} // namespace cedar
