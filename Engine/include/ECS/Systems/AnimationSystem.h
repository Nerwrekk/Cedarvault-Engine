#pragma once

#include "ECS/Components/Components.h"

namespace cedar
{
	class AnimationSystem : public BaseSystem
	{
	public:
		AnimationSystem()
		{
			RequireComponent<SpriteComponent>();
			RequireComponent<AnimationComponent>();
		}

		virtual void Update(double deltaTime) override
		{
		}
	};
} // namespace cedar
