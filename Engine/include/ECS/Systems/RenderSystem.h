#pragma once

#include "ECS/Components/Components.h"
#include "Common/SDL_Wrapper.h"
#include "Common/AssetManager.h"

#include <algorithm>

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
			//Note to self, cant sort a const vector! ;)
			auto& entities = GetSystemEntities();
			//Sort all entities based on ZIndex and Y transformPosition
			std::sort(entities.begin(), entities.end(), [](const Entity& first, const Entity& second)
			{
				auto firstEntityTransform = first.GetComponent<TransformComponent>();
				auto firstEntitySpriteComponent = first.GetComponent<SpriteComponent>();

				auto secondEntityTransform = second.GetComponent<TransformComponent>();
				auto secondEntitySpriteComponent = second.GetComponent<SpriteComponent>();

				//first check if they have the same Zindex
				if (firstEntitySpriteComponent->ZIndex == secondEntitySpriteComponent->ZIndex)
				{
					//Zindex match so we sort by Y transform position
					return firstEntityTransform->Position.y < secondEntityTransform->Position.y;
				}

				//if they dont have the same Zindex we sort by Zindex
				return firstEntitySpriteComponent->ZIndex < secondEntitySpriteComponent->ZIndex;
			});

			for (auto& entity : entities)
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
