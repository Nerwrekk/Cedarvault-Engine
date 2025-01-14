#pragma once

#include "ECS/Components/Components.h"
#include "Common/SDL_Wrapper.h"
#include "Common/AssetManager.h"

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

				SDL_Texture* texture = AssetManager::Inst()->GetTexture(spriteComponent->TextureId);

				SDL_Rect srcRect = spriteComponent->SrcRect;

				//Destination rectangle that we want to place our texture.
				SDL_Rect dstRect = {
					static_cast<int>(transform->Position.x),
					static_cast<int>(transform->Position.y),
					static_cast<int>(spriteComponent->Width * transform->Scale.x),
					static_cast<int>(spriteComponent->Height * transform->Scale.y)
				};

				SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, transform->Rotation, nullptr, SDL_FLIP_NONE);
			}
		}
	};
} // namespace cedar
