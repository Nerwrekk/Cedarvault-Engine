#include "Common/Input.h"

#include <SDL2/SDL.h>

namespace cedar
{
	const Uint8* currentKeyState;
	Uint8 previousKeyState[SDL_NUM_SCANCODES]; // Store previous state

	bool Input::IsKeyPressed(const KeyCode key)
	{
		return currentKeyState[key] && !previousKeyState[key];

		auto state = SDL_GetKeyboardState(nullptr);

		return state[key] ? true : false;
	}

	bool Input::IsKeyReleased(const KeyCode key)
	{
		return !currentKeyState[key] && previousKeyState[key];
	}

	bool Input::IsKeyRepeated(const KeyCode key)
	{
		return currentKeyState[key] && previousKeyState[key]; // Held down (repeat)
	}

	void Input::UpdateKeyStates()
	{
		SDL_memcpy(previousKeyState, currentKeyState, SDL_NUM_SCANCODES);
		currentKeyState = SDL_GetKeyboardState(NULL);
	}

	void Input::InitKeyStates()
	{
		currentKeyState = SDL_GetKeyboardState(NULL);
		SDL_memset(previousKeyState, 0, SDL_NUM_SCANCODES);
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