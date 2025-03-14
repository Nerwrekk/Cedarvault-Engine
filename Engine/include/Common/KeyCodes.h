#pragma once

#include <stdint.h>

namespace cedar
{
	using KeyCode = uint16_t;

	namespace Key
	{
		// From glfw3.h
		// enum : KeyCode
		// {
		// 	Space = 32,
		// 	Apostrophe = 39, /* ' */
		// 	Comma = 44,      /* , */
		// 	Minus = 45,      /* - */
		// 	Period = 46,     /* . */
		// 	Slash = 47,      /* / */

		// 	Num_0 = 48, /* 0 */
		// 	Num_1 = 49, /* 1 */
		// 	Num_2 = 50, /* 2 */
		// 	Num_3 = 51, /* 3 */
		// 	Num_4 = 52, /* 4 */
		// 	Num_5 = 53, /* 5 */
		// 	Num_6 = 54, /* 6 */
		// 	Num_7 = 55, /* 7 */
		// 	Num_8 = 56, /* 8 */
		// 	Num_9 = 57, /* 9 */

		// 	Semicolon = 59, /* ; */
		// 	Equal = 61,     /* = */

		// 	A = 65,
		// 	B = 66,
		// 	C = 67,
		// 	D = 68,
		// 	E = 69,
		// 	F = 70,
		// 	G = 71,
		// 	H = 72,
		// 	I = 73,
		// 	J = 74,
		// 	K = 75,
		// 	L = 76,
		// 	M = 77,
		// 	N = 78,
		// 	O = 79,
		// 	P = 80,
		// 	Q = 81,
		// 	R = 82,
		// 	S = 83,
		// 	T = 84,
		// 	U = 85,
		// 	V = 86,
		// 	W = 87,
		// 	X = 88,
		// 	Y = 89,
		// 	Z = 90,

		// 	LeftBracket = 91,  /* [ */
		// 	Backslash = 92,    /* \ */
		// 	RightBracket = 93, /* ] */
		// 	GraveAccent = 96,  /* ` */

		// 	World1 = 161, /* non-US #1 */
		// 	World2 = 162, /* non-US #2 */

		// 	/* Function keys */
		// 	Escape = 256,
		// 	Enter = 257,
		// 	Tab = 258,
		// 	Backspace = 259,
		// 	Insert = 260,
		// 	Delete = 261,
		// 	Right = 262,
		// 	Left = 263,
		// 	Down = 264,
		// 	Up = 265,
		// 	PageUp = 266,
		// 	PageDown = 267,
		// 	Home = 268,
		// 	End = 269,
		// 	CapsLock = 280,
		// 	ScrollLock = 281,
		// 	NumLock = 282,
		// 	PrintScreen = 283,
		// 	Pause = 284,
		// 	F1 = 290,
		// 	F2 = 291,
		// 	F3 = 292,
		// 	F4 = 293,
		// 	F5 = 294,
		// 	F6 = 295,
		// 	F7 = 296,
		// 	F8 = 297,
		// 	F9 = 298,
		// 	F10 = 299,
		// 	F11 = 300,
		// 	F12 = 301,
		// 	F13 = 302,
		// 	F14 = 303,
		// 	F15 = 304,
		// 	F16 = 305,
		// 	F17 = 306,
		// 	F18 = 307,
		// 	F19 = 308,
		// 	F20 = 309,
		// 	F21 = 310,
		// 	F22 = 311,
		// 	F23 = 312,
		// 	F24 = 313,
		// 	F25 = 314,

		// 	/* Keypad */
		// 	KP0 = 320,
		// 	KP1 = 321,
		// 	KP2 = 322,
		// 	KP3 = 323,
		// 	KP4 = 324,
		// 	KP5 = 325,
		// 	KP6 = 326,
		// 	KP7 = 327,
		// 	KP8 = 328,
		// 	KP9 = 329,
		// 	KPDecimal = 330,
		// 	KPDivide = 331,
		// 	KPMultiply = 332,
		// 	KPSubtract = 333,
		// 	KPAdd = 334,
		// 	KPEnter = 335,
		// 	KPEqual = 336,

		// 	LeftShift = 340,
		// 	LeftControl = 341,
		// 	LeftAlt = 342,
		// 	LeftSuper = 343,
		// 	RightShift = 344,
		// 	RightControl = 345,
		// 	RightAlt = 346,
		// 	RightSuper = 347,
		// 	Menu = 348,

		// 	Key_Last = 348
		// };

		//from sdl
		enum : KeyCode
		{
			//TODO: Fix and add the correct Keycode values
			Space = 44,
			Apostrophe = 0x27, /* ' */
			Comma = 0x2C,      /* , */
			Minus = 0x2D,      /* - */
			Period = 0x2E,     /* . */
			Slash = 0x2F,      /* / */

			Num_0 = 0x30, /* 0 */
			Num_1 = 0x31, /* 1 */
			Num_2 = 0x32, /* 2 */
			Num_3 = 0x33, /* 3 */
			Num_4 = 0x34, /* 4 */
			Num_5 = 0x35, /* 5 */
			Num_6 = 0x36, /* 6 */
			Num_7 = 0x37, /* 7 */
			Num_8 = 0x38, /* 8 */
			Num_9 = 0x39, /* 9 */

			Semicolon = 0x3B, /* ; */
			Equal = 0x3D,     /* = */

			A = 0x04,
			B = 0x05,
			C = 0x06,
			D = 0x07,
			E = 0x08,
			F = 0x09,
			G = 0x0A,
			H = 0x0B,
			I = 0x0C,
			J = 0x0D,
			K = 0x0E,
			L = 0x0F,
			M = 0x10,
			N = 0x11,
			O = 0x12,
			P = 0x13,
			Q = 0x14,
			R = 0x15,
			S = 0x16,
			T = 0x17,
			U = 0x18,
			V = 0x19,
			W = 0x1A,
			X = 0x1B,
			Y = 0x1C,
			Z = 0x1D,

			LeftBracket = 0x1E,  /* [ */
			Backslash = 0x2B,    /* \ */
			RightBracket = 0x1F, /* ] */
			GraveAccent = 0x29,  /* ` */

			World1 = 0x100, /* non-US #1 */
			World2 = 0x101, /* non-US #2 */

			Escape = 0x01,
			Enter = 0x28,
			Tab = 0x2B,
			Backspace = 0x2A,
			Insert = 0x152,
			Delete = 0x151,
			Right = 0x4F,
			Left = 0x50,
			Down = 0x51,
			Up = 0x52,
			PageUp = 0x4B,
			PageDown = 0x4E,
			Home = 0x47,
			End = 0x4F,
			CapsLock = 0x3A,
			ScrollLock = 0x46,
			NumLock = 0x45,
			PrintScreen = 0x46,
			Pause = 0x13,
			F1 = 0x3A,
			F2 = 0x3B,
			F3 = 0x3C,
			F4 = 0x3D,
			F5 = 0x3E,
			F6 = 0x3F,
			F7 = 0x40,
			F8 = 0x41,
			F9 = 0x42,
			F10 = 0x43,
			F11 = 0x44,
			F12 = 0x45,
			F13 = 0x100,
			F14 = 0x101,
			F15 = 0x102,
			F16 = 0x103,
			F17 = 0x104,
			F18 = 0x105,
			F19 = 0x106,
			F20 = 0x107,
			F21 = 0x108,
			F22 = 0x109,
			F23 = 0x10A,
			F24 = 0x10B,
			F25 = 0x10C,

			KP0 = 0x52,
			KP1 = 0x4F,
			KP2 = 0x50,
			KP3 = 0x51,
			KP4 = 0x4B,
			KP5 = 0x4C,
			KP6 = 0x4D,
			KP7 = 0x47,
			KP8 = 0x48,
			KP9 = 0x49,
			KPDecimal = 0x53,
			KPDivide = 0xB5,
			KPMultiply = 0xB6,
			KPSubtract = 0xB4,
			KPAdd = 0xB3,
			KPEnter = 0xA8,
			KPEqual = 0xB7,

			LeftShift = 0xE1,
			LeftControl = 0xE0,
			LeftAlt = 0xE2,
			LeftSuper = 0xE3,
			RightShift = 0xE4,
			RightControl = 0xE5,
			RightAlt = 0xE6,
			RightSuper = 0xE7,
			Menu = 0x100,

			Key_Last = 0x100
		};
	}
}