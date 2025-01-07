#pragma once

#include "ECS/Components/Components.h"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>

namespace cedar
{
	class RenderSystem : public BaseSystem
	{
	public:
		RenderSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<SpriteComponent>();
		}

		virtual void Update(double deltaTime) override
		{
			//RenderSystem is a bit special and do not need this
		}

		void RenderEntites(SDL_Renderer* renderer)
		{
			for (auto& entity : GetSystemEntities())
			{
				auto transform = entity.GetComponent<TransformComponent>();
				auto spriteComponent = entity.GetComponent<SpriteComponent>();

				SDL_Surface* surface = IMG_Load(spriteComponent->SpritePath.c_str());
				SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);

				//Destination rectangle that we want to place our texture.
				SDL_Rect dstRect = { static_cast<int>(transform->Position.x), static_cast<int>(transform->Position.y), 32, 32 };
				SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

				SDL_DestroyTexture(texture);
			}
		}
	};
} // namespace cedar
