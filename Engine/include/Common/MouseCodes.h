#pragma once

#include <stdint.h>

namespace cedar
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		// From glfw3.h
		// enum : MouseCode
		// {
		// 	Button0 = 0,
		// 	Button1 = 1,
		// 	Button2 = 2,
		// 	Button3 = 3,
		// 	Button4 = 4,
		// 	Button5 = 5,
		// 	Button6 = 6,
		// 	Button7 = 7,

		// 	ButtonLast = Button7,
		// 	ButtonLeft = Button0,
		// 	ButtonRight = Button1,
		// 	ButtonMiddle = Button2
		// };

		// From sdl
		enum : MouseCode
		{
			MB_Left   = 1,
			MB_Middle = 2,
			MB_Right  = 3,
			MB_X1     = 4,
			MB_X2     = 5,
			Button5   = 6,
			Button6   = 7,
			Button7   = 8,

			ButtonLast   = Button7,
			ButtonLeft   = MB_Left,
			ButtonRight  = MB_Right,
			ButtonMiddle = MB_Middle
		};
	}
}