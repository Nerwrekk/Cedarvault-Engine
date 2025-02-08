#pragma once

#include "Common/SDL_Wrapper.h"
#include "ECS/Components/Components.h"

namespace cedar
{
	class CollisionSystem : public BaseSystem
	{
	public:
		CollisionSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<AnimationComponent>();
		}

		virtual void Update(double deltaTime) override
		{
			for (auto& entity : GetSystemEntities())
			{
			}
		}
	};
} // namespace cedar
