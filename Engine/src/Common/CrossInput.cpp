#include "Common/Input.h"

#include <SDL2/SDL.h>
#include <array>

namespace cedar
{
	// Keyboard button state arrays
	constexpr int MB_Count = 5;
	constexpr int NUM_KEYS = SDL_NUM_SCANCODES;

	inline std::array<bool, NUM_KEYS> currentKeyState {};
	inline std::array<bool, NUM_KEYS> previousKeyState {};

	inline std::array<bool, NUM_KEYS> keysPressed {};
	inline std::array<bool, NUM_KEYS> keysReleased {};

	// Mouse button state arrays
	inline std::array<bool, MB_Count> mouseDown {};
	inline std::array<bool, MB_Count> prevMouseDown {};
	inline std::array<bool, MB_Count> mousePressed {};
	inline std::array<bool, MB_Count> mouseReleased {};

	inline int mouseX = 0, mouseY = 0;
	inline int prevMouseX = 0, prevMouseY = 0;
	inline int mouseDeltaX = 0, mouseDeltaY = 0;
	inline float mouseWheelDelta = 0.0f;

	bool Input::IsKeyPressed(const KeyCode key)
	{
		return keysPressed[key];
	}

	bool Input::IsKeyReleased(const KeyCode key)
	{
		return keysReleased[key];
	}

	bool Input::IsKeyRepeated(const KeyCode key)
	{
		return currentKeyState[key];
	}

	void Input::UpdateKeyStates()
	{
		const Uint8* newKeyState = SDL_GetKeyboardState(NULL);
		memcpy(currentKeyState.data(), newKeyState, NUM_KEYS);
	}

	void Input::ComputeFixedUpdateKeyEdges()
	{
		for (int i = 0; i < NUM_KEYS; i++)
		{
			keysPressed[i]  = currentKeyState[i] && !previousKeyState[i];
			keysReleased[i] = !currentKeyState[i] && previousKeyState[i];
		}

		memcpy(previousKeyState.data(), currentKeyState.data(), NUM_KEYS);
	}

	//TODO: might not need this anymore, maybe remove
	void Input::InitKeyStates()
	{
		// currentKeyState = SDL_GetKeyboardState(NULL);
		// SDL_memset(previousKeyState, 0, SDL_NUM_SCANCODES);
	}

	void Input::UpdateMouseState()
	{
		//Get button staten and mouse pos
		Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

		std::array<bool, MB_Count> current {};
		mouseDown[0] = (buttons & SDL_BUTTON(SDL_BUTTON_LEFT));
		mouseDown[1] = (buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE));
		mouseDown[2] = (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT));
		mouseDown[3] = (buttons & SDL_BUTTON(SDL_BUTTON_X1));
		mouseDown[4] = (buttons & SDL_BUTTON(SDL_BUTTON_X2));

		//Update mouse delta positoon
		mouseDeltaX = mouseX - prevMouseX;
		mouseDeltaY = mouseY - prevMouseY;
	}

	void Input::ComputeFixedUpdateMouseEdges()
	{
		for (int i = 0; i < MB_Count; ++i)
		{
			mousePressed[i]  = mouseDown[i] && !prevMouseDown[i];
			mouseReleased[i] = !mouseDown[i] && prevMouseDown[i];
			prevMouseDown[i] = mouseDown[i];
		}

		// For position interpolation: we keep prevMouseX/Y updated here too
		prevMouseX = mouseX;
		prevMouseY = mouseY;
	}

	bool Input::IsMouseButtonDown(const MouseCode button)
	{
		return mouseDown[button - 1];
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		return mousePressed[button - 1];
	}

	bool Input::IsMouseButtonReleased(const MouseCode button)
	{
		return mouseReleased[button - 1];
	}

	glm::vec2 Input::GetMousePosition()
	{
		return glm::vec2(mouseX, mouseY);
	}

	glm::vec2 Input::GetMouseDelta()
	{
		return glm::vec2(mouseDeltaX, mouseDeltaY);
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

	float Input::GetMouseWheelDelta()
	{
		return mouseWheelDelta;
	}

	void Input::SetRelativeMouseMode(bool enabled)
	{
		SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE);
	}

	bool Input::IsRelativeMouseMode()
	{
		return SDL_GetRelativeMouseMode() == SDL_TRUE;
	}
}