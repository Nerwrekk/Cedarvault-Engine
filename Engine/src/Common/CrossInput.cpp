#include "Common/Input.h"

#include <SDL2/SDL.h>
#include <array>

namespace cedar
{
	constexpr int NUM_KEYS = SDL_NUM_SCANCODES;

	inline std::array<bool, NUM_KEYS> currentKeyState {};
	inline std::array<bool, NUM_KEYS> previousKeyState {}; // Snapshot from last tick

	inline std::array<bool, NUM_KEYS> keysPressed {};
	inline std::array<bool, NUM_KEYS> keysReleased {};

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

		// Snapshot for next tick
		memcpy(previousKeyState.data(), currentKeyState.data(), NUM_KEYS);
	}

	//TODO: might not need this anymore, maybe remove
	void Input::InitKeyStates()
	{
		// currentKeyState = SDL_GetKeyboardState(NULL);
		// SDL_memset(previousKeyState, 0, SDL_NUM_SCANCODES);
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto state = SDL_GetMouseState(nullptr, nullptr);

		return (state & SDL_BUTTON(button));
	}

	glm::vec2 Input::GetMousePosition()
	{
		int32_t xPos {}, yPos {};
		auto state = SDL_GetMouseState(&xPos, &yPos);

		return glm::vec2(xPos, yPos);
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}