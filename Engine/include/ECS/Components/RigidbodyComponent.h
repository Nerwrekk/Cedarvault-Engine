#pragma once

#include "Common/Core.h"

#include <glm/glm.hpp>

namespace cedar
{
	struct CEDAR_API RigidBodyComponent
	{
		DECL_TYPE_NAME(RigidBodyComponent)

		glm::vec2 Velocity;

		RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0))
		{
			this->Velocity = velocity;
		}
	};

} // namespace cedar