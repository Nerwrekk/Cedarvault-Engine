#pragma once

#include "ECS/Components/Components.h"

namespace cedar
{
	class CameraFollowSystem : public BaseSystem
	{
		CameraFollowSystem()
		{
			RequireComponent<CameraFollowComponent>();
			RequireComponent<TransformComponent>();
		}

		virtual void Update() override
		{
			for (auto entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
			}
		}
	};
} // namespace cedar
