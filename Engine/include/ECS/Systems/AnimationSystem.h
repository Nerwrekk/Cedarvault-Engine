#pragma once

#include "Common/SDL_Wrapper.h"
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
			for (auto& entity : GetSystemEntities())
			{
				auto spriteComp = entity.GetComponent<SpriteComponent>();
				auto animComp = entity.GetComponent<AnimationComponent>();
				CEDAR_DEBUG("CurrentFrameCalculation: {}", ((SDL_GetTicks() - animComp->StartTime) * animComp->FrameRateSpeed / 1000));
				CEDAR_DEBUG("CurrentFrameCalculation with module: {}", ((SDL_GetTicks() - animComp->StartTime) * animComp->FrameRateSpeed / 1000) % animComp->NumOfFrames);
				animComp->CurrentFrame = ((SDL_GetTicks() - animComp->StartTime) * animComp->FrameRateSpeed / 1000) % animComp->NumOfFrames;
				spriteComp->SrcRect.x = animComp->CurrentFrame * spriteComp->Width;
			}
		}
	};
} // namespace cedar
