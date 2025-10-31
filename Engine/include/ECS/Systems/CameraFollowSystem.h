#pragma once

#include "ECS/Components/Components.h"
#include "Common/Logger.h"

#include <SDL.h>

namespace cedar
{
	class CameraFollowSystem : public BaseSystem
	{
	public:
		DECL_TYPE_NAME(CameraFollowSystem);

		CameraFollowSystem()
		{
			RequireComponent<CameraFollowComponent>();
			RequireComponent<TransformComponent>();
		}
		const float followSpeed = 1.0f; // tweak as needed

		virtual void LateUpdate() override
		{
			auto camera         = Application::Get().Camera();
			auto gameSetting    = &Application::Get().GameSetting;
			const float EPSILON = 0.25f; // tweak: half a pixel-ish
			for (auto entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
				// compute target from transform (use interpolated transform if available)
				float targetX = transform->Position.x - (gameSetting->WindowWidth * 0.5f);
				float targetY = transform->Position.y - (gameSetting->WindowHeight * 0.5f);

				// Smooth follow (exponential smoothing)
				camera->x += (targetX - camera->x) * followSpeed * Time::DeltaTime;
				camera->y += (targetY - camera->y) * followSpeed * Time::DeltaTime;

				// Snap when very close to avoid flip-flop around integer boundary
				if (std::fabs(targetX - camera->x) < EPSILON)
				{
					camera->x = targetX;
				}
				if (std::fabs(targetY - camera->y) < EPSILON)
				{
					camera->y = targetY;
				}

				// Clamp
				int maxCamX = static_cast<int>(gameSetting->MapWidth) - camera->w;
				int maxCamY = static_cast<int>(gameSetting->MapHeight) - camera->h;
				camera->x   = std::clamp(camera->x, 0, std::max(0, maxCamX));
				camera->y   = std::clamp(camera->y, 0, std::max(0, maxCamY));

				// only at the end, convert to integers for the SDL_Rect used by renderer
				camera->x = static_cast<int>(std::lround(camera->x));
				camera->y = static_cast<int>(std::lround(camera->y));
			}
		}
	};
} // namespace cedar
