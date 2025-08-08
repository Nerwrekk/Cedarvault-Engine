#pragma once

#include "Common/SDL_Wrapper.h"

namespace cedar
{
	struct AnimationComponent
	{
		int NumOfFrames;
		int CurrentFrame;
		int FrameRateSpeed;
		int StartTime;
		bool ShouldLoop;

		AnimationComponent(int numOfFrames = 1, int frameRateSpeed = 1, bool shouldLoop = false)
		{
			this->NumOfFrames = numOfFrames;
			this->CurrentFrame = 1;
			this->FrameRateSpeed = frameRateSpeed;
			this->ShouldLoop = shouldLoop;
			this->StartTime = SDL_GetTicks();
		}
	};
} // namespace cedar
