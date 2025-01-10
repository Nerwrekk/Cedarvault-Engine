#pragma once

#include "ECS/Components/Components.h"

#include "Common/SDL_Wrapper.h"

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

				//Destination rectangle that we want to place our texture.
				SDL_Rect dstRect = {
					static_cast<int>(transform->Position.x),
					static_cast<int>(transform->Position.y),
					spriteComponent->Width,
					spriteComponent->Height
				};
				SDL_RenderCopy(renderer, spriteComponent->Texture, nullptr, &dstRect);

				// SDL_DestroyTexture(spriteComponent->Texture);
			}
		}
	};
} // namespace cedar
