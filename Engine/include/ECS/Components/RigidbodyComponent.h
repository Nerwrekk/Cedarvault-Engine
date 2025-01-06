#pragma once

#include <glm/glm.hpp>

namespace cedar
{
	struct RigidBodyComponent
	{
		glm::vec2 Velocity;

		RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0))
		{
			this->Velocity = velocity;
		}
	};

} // namespace cedar