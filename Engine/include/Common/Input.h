#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace cedar
{
	class Input
	{
	public:
		static void InitKeyStates();
		static void UpdateKeyStates();
		static void ComputeFixedUpdateKeyEdges();

		static bool IsKeyPressed(const KeyCode key);
		static bool IsKeyReleased(const KeyCode key);
		static bool IsKeyRepeated(const KeyCode key);

		static void UpdateMouseState();
		static void ComputeFixedUpdateMouseEdges();

		static bool IsMouseButtonDown(const MouseCode button);
		static bool IsMouseButtonPressed(const MouseCode button);
		static bool IsMouseButtonReleased(const MouseCode button);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		static glm::vec2 GetMouseDelta();
		static float GetMouseWheelDelta();

		static void SetRelativeMouseMode(bool enabled);
		static bool IsRelativeMouseMode();
	};
}