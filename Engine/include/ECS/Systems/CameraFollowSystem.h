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

				if (transform->Position.x + (camera->w / 2) < gameSetting->MapWidth)
				{
					camera->x = static_cast<int>(transform->Position.x) - (gameSetting->WindowWidth / 2);
				}

				if (transform->Position.y + (camera->h / 2) < gameSetting->MapHeight)
				{
					camera->y = static_cast<int>(transform->Position.y) - (gameSetting->WindowHeight / 2);
				}
				camera->x = camera->x < 0 ? 0 : camera->x;
				camera->y = camera->y < 0 ? 0 : camera->y;

				camera->x = camera->x > camera->w ? camera->w : camera->x;
				camera->y = camera->y > camera->h ? camera->h : camera->y;
			}
		}
	};
} // namespace cedar
