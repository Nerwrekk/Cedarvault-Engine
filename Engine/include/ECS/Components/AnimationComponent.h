#pragma once

#include "Common/Core.h"
#include "Common/SDL_Wrapper.h"

namespace cedar
{
	struct CEDAR_API AnimationComponent
	{
		DECL_TYPE_NAME(AnimationComponent);

		int NumOfFrames;
		int CurrentFrame;
		int FrameRateSpeed;
		int StartTime;
		bool ShouldLoop;

		AnimationComponent(int numOfFrames = 1, int frameRateSpeed = 1, bool shouldLoop = false)
		{
			this->NumOfFrames    = numOfFrames;
			this->CurrentFrame   = 1;
			this->FrameRateSpeed = frameRateSpeed;
			this->ShouldLoop     = shouldLoop;
			this->StartTime      = SDL_GetTicks();
		}
	};
} // namespace cedar
