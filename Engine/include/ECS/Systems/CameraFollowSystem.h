#pragma once

#include "ECS/Components/Components.h"
#include "Common/Logger.h"

#include <SDL.h>

namespace cedar
{
	class CameraFollowSystem : public BaseSystem
	{
	public:
		CameraFollowSystem()
		{
			RequireComponent<CameraFollowComponent>();
			RequireComponent<TransformComponent>();
		}

		virtual void Update() override
		{
			auto camera = Application::Get().Camera();
			auto gameSetting = &Application::Get().GameSetting;
			for (auto entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();

				if (transform->Position.x < gameSetting->MapWidth)
				{
					camera->x = transform->Position.x;
				}

				if (transform->Position.y < gameSetting->MapHeight)
				{
					camera->y = transform->Position.y;
				}
				camera->x = camera->x < 0 ? 0 : camera->x;
				camera->y = camera->y < 0 ? 0 : camera->y;

				camera->x = camera->x > camera->w ? camera->w : camera->x;
				camera->y = camera->y > camera->h ? camera->h : camera->y;
			}
		}
	};
} // namespace cedar
