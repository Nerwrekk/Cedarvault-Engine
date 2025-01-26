#pragma once

namespace cedar
{
	struct AnimationComponent
	{
		int NumOfFrames;
		int CurrentFrame;
		int FrameRateSpeed;
		bool ShouldLoop;

		AnimationComponent(int numOfFrames = 1, int frameRateSpeed = 1, bool shouldLoop = false)
		{
			this->NumOfFrames = numOfFrames;
			this->CurrentFrame = 1;
			this->FrameRateSpeed = frameRateSpeed;
			this->ShouldLoop = shouldLoop;
		}
	};
} // namespace cedar
