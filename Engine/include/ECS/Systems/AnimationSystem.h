#pragma once

#include "Common/SDL_Wrapper.h"
#include "ECS/Components/Components.h"
#include "Common/AssetManager.h"

namespace cedar
{
	class AnimationSystem : public BaseSystem
	{
	public:
		DECL_TYPE_NAME(AnimationSystem);

		AnimationSystem()
		{
			RequireComponent<SpriteComponent>();
			RequireComponent<AnimationComponent>();
		}

		virtual void FixedUpdate(float fixedDeltaTime) override
		{
			UNREFERENCED_PARAMETER(fixedDeltaTime);

			for (auto& entity : GetSystemEntities())
			{
				auto spriteComp = entity.GetComponent<SpriteComponent>();
				auto animComp   = entity.GetComponent<AnimationComponent>();
				auto sprite     = AssetManager::Inst()->GetSprite(spriteComp->TextureId.GetString());
				// CEDAR_DEBUG("CurrentFrameCalculation: {}", ((SDL_GetTicks() - animComp->StartTime) * animComp->FrameRateSpeed / 1000));
				// CEDAR_DEBUG("CurrentFrameCalculation with module: {}", ((SDL_GetTicks() - animComp->StartTime) * animComp->FrameRateSpeed / 1000) % animComp->NumOfFrames);
				animComp->CurrentFrame = ((SDL_GetTicks() - animComp->StartTime) * animComp->FrameRateSpeed / 1000) % animComp->NumOfFrames;
				auto srcWidth          = (sprite->Width / animComp->NumOfFrames);
				sprite->SrcRect.x      = animComp->CurrentFrame * srcWidth;
				sprite->SrcRect.w      = srcWidth;
			}
		}
	};
} // namespace cedar
