#pragma once

#include "ECS/Components/Components.h"
#include "Common/Logger.h"

#include <cmath>
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
		// smoothing params
		const float followSpeed = 8.0f; // tweak: higher = snappier, lower = looser

		virtual void LateUpdate() override
		{
			Camera* camera   = Application::Get().GetMainCamera(); // ensure this returns pointer/ref to actual camera
			auto gameSetting = &Application::Get().GameSetting;

			// compute exponential smoothing factor from dt (recommended)
			// float k = 1.0f - std::expf(-followSpeed * Time::DeltaTime); // in (0,1)

			for (auto entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
				if (!transform) continue;

				// target camera center (float)
				float targetX = transform->Position.x - (gameSetting->WindowWidth * 0.5f);
				float targetY = transform->Position.y - (gameSetting->WindowHeight * 0.5f);

				// Smooth follow using damping (frame-rate independent)
				camera->X += (targetX - camera->X); // * k;
				camera->Y += (targetY - camera->Y); // * k;

				// clamp camera floats to map bounds
				int maxCamX = static_cast<int>(gameSetting->MapWidth) - camera->Rect.w;
				int maxCamY = static_cast<int>(gameSetting->MapHeight) - camera->Rect.h;
				camera->X   = std::clamp(camera->X, 0.0f, float(std::max(0, maxCamX)));
				camera->Y   = std::clamp(camera->Y, 0.0f, float(std::max(0, maxCamY)));

				// DO NOT round / assign camera->Rect.x/y here
			}
		}
	};
} // namespace cedar
