#pragma once

#include <glm/glm.hpp>

namespace cedar
{
	struct TransformComponent : public BaseComponent
	{
		glm::vec2 Position;
		glm::vec2 Scale;
		double Rotation;
	};
} // namespace cedar
