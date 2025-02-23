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
			Button0 = 1,
			Button1 = 2,
			Button2 = 3,
			Button3 = 4,
			Button4 = 5,
			Button5 = 6,
			Button6 = 7,
			Button7 = 8,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button3,
			ButtonMiddle = Button2
		};
	}
}