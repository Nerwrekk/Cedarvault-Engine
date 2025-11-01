#pragma once

namespace cedar
{
	// fixed-step settings
	const int FPS                   = 60;
	const double FIXED_DT           = 1.0 / FPS; // seconds per update
	const double MAX_ACCUM          = 0.25;      // clamp accumulator to avoid spiral
	const int MAX_UPDATES_PER_FRAME = 10;
} // namespace cedar
