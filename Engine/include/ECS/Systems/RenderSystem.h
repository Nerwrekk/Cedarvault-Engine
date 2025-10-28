#pragma once

#include "ECS/Components/Components.h"
#include "Application/Application.h"
#include "Common/SDL_Wrapper.h"
#include "Common/AssetManager.h"

#include <algorithm>

namespace cedar
{
	class RenderSystem : public BaseSystem
	{
	public:
		DECL_TYPE_NAME(RenderSystem);

		RenderSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<SpriteComponent>();
		}

		virtual void Update() override
		{
			//RenderSystem is a bit special and do not need this
		}

	private:
		void SortEntities(std::vector<Entity>& entities)
		{
			//Sort all entities based on ZIndex and Y transformPosition
			std::sort(entities.begin(), entities.end(), [](const Entity& first, const Entity& second)
			{
				auto firstEntityTransform       = first.GetComponent<TransformComponent>();
				auto firstEntitySpriteComponent = first.GetComponent<SpriteComponent>();

				auto secondEntityTransform       = second.GetComponent<TransformComponent>();
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
		}

	public:
		void RenderEntites(SDL_Renderer* renderer)
		{
			//Note to self, cant sort a const vector! ;)
			SortEntities(GetSystemEntities());
			auto camera = Application::Get().Camera();
			for (auto& entity : GetSystemEntities())
			{
				auto transform       = entity.GetComponent<TransformComponent>();
				auto spriteComponent = entity.GetComponent<SpriteComponent>();

				SDL_Texture* texture = AssetManager::Inst()->GetTexture(spriteComponent->TextureId.GetString());

				SDL_Rect srcRect = spriteComponent->SrcRect;

				//Destination rectangle that we want to place our texture.
				SDL_Rect dstRect = {
					static_cast<int>(transform->Position.x - camera->x),
					static_cast<int>(transform->Position.y - camera->y),
					static_cast<int>(spriteComponent->Width * transform->Scale.x),
					static_cast<int>(spriteComponent->Height * transform->Scale.y)
				};

				SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, transform->Rotation, nullptr, SDL_FLIP_NONE);

				auto boxCollider = entity.GetComponent<BoxColliderComponent>();
				if (boxCollider)
				{
					float xPos = transform->Position.x;
					float yPos = transform->Position.y;
					xPos += boxCollider->Offset.x;
					yPos += boxCollider->Offset.y;

					SDL_Rect colliderRect = {
						static_cast<int>(xPos - camera->x),
						static_cast<int>(yPos - camera->y),
						static_cast<int>(boxCollider->Width),
						static_cast<int>(boxCollider->Height),
					};
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green color
					SDL_RenderDrawRect(renderer, &colliderRect);
				}
			}
		}
	};
} // namespace cedar
