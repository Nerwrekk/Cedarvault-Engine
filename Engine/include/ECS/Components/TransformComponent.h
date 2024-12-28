#pragma once

#include <glm/glm.hpp>

namespace cedar
{
	struct TransformComponent : public Component
	{
		glm::vec2 Position;
		glm::vec2 Scale;
		double Rotation;
	};
} // namespace cedar
