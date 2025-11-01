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
		void RenderEntites(SDL_Renderer* renderer, float alpha)
		{
			SortEntities(GetSystemEntities());

			// Interpolate camera position (assume Camera() returns current camera with x,y and prevX, prevY set)
			auto camera = Application::Get().GetMainCamera();
			float camX  = camera->PrevX + alpha * (camera->X - camera->PrevX);
			float camY  = camera->PrevY + alpha * (camera->Y - camera->PrevY);

			// only here: update integer rect for SDL rendering
			camera->Rect.x = static_cast<int>(std::lround(camX));
			camera->Rect.y = static_cast<int>(std::lround(camY));

			// Iterate the actual entity list once
			for (auto& entity : GetSystemEntities())
			{
				auto transform       = entity.GetComponent<TransformComponent>();
				auto spriteComponent = entity.GetComponent<SpriteComponent>();

				SDL_Texture* texture = AssetManager::Inst()->GetTexture(spriteComponent->TextureId.GetString());
				SDL_Rect srcRect     = spriteComponent->SrcRect;

				// Interpolate transform position and rotation
				glm::vec2 renderPos   = glm::mix(transform->PrevPosition, transform->Position, alpha);
				double renderRot      = transform->Rotation + alpha * (transform->Rotation - transform->PrevRotation);
				glm::vec2 renderScale = transform->Scale; // scale rarely needs interpolation, but you can if required

				// Build destination rect using interpolated values and camera
				// Use float -> int conversion consistently (round or floor as you prefer)
				int dstX = static_cast<int>(std::round(renderPos.x - camX));
				int dstY = static_cast<int>(std::round(renderPos.y - camY));
				int dstW = static_cast<int>(std::round(spriteComponent->Width * renderScale.x));
				int dstH = static_cast<int>(std::round(spriteComponent->Height * renderScale.y));

				SDL_Rect dstRect { dstX, dstY, dstW, dstH };

				// Render (rotation in degrees). Do NOT mutate transform here.
				SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, renderRot, nullptr, SDL_FLIP_NONE);

				// Debug collider draw (interpolate collider offset too if needed)
				auto boxCollider = entity.GetComponent<BoxColliderComponent>();
				if (boxCollider)
				{
					float xPos = renderPos.x + boxCollider->Offset.x;
					float yPos = renderPos.y + boxCollider->Offset.y;

					SDL_Rect colliderRect {
						static_cast<int>(std::round(xPos - camX)),
						static_cast<int>(std::round(yPos - camY)),
						static_cast<int>(std::round(boxCollider->Width)),
						static_cast<int>(std::round(boxCollider->Height))
					};

					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderDrawRect(renderer, &colliderRect);
				}
			}
		}
	};
} // namespace cedar
