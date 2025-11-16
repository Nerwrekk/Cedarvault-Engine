#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace cedar
{
	class Input
	{
	public:
		static bool IsKeyPressed(const KeyCode key);
		static bool IsKeyReleased(const KeyCode key);
		static bool IsKeyRepeated(const KeyCode key);

		static void ComputeFixedUpdateKeyEdges();

		static bool IsMouseButtonPressed(const MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		static void InitKeyStates();
		static void UpdateKeyStates();
	};
}