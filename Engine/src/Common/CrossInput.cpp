#include "Common/Input.h"

#include <SDL2/SDL.h>

namespace cedar
{
	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto state = SDL_GetKeyboardState(nullptr);

		return state[key] ? true : false;
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