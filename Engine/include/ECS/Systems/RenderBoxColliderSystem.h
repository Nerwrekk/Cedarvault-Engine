#pragma once

#include "Common/SDL_Wrapper.h"
#include "Application/Application.h"
#include "ECS/Components/Components.h"
#include "Common/CedarTime.h"

#include <map>

namespace cedar
{
	class RenderBoxColliderSystem : public BaseSystem
	{
	public:
		DECL_TYPE_NAME(RenderBoxColliderSystem);

		RenderBoxColliderSystem()
		{
			RequireComponent<BoxColliderComponent>();
			RequireComponent<TransformComponent>();

			RedColour.r = 255;
			RedColour.g = 0;
			RedColour.b = 0;
			RedColour.a = 255;

			GreenColour.r = 0;
			GreenColour.g = 255;
			GreenColour.b = 0;
			GreenColour.a = 255;

			boxColour = GreenColour;

			EventBus::Inst()->Subscribe<CollisionEnterEvent>(this, &RenderBoxColliderSystem::OnCollidingEnter);
			EventBus::Inst()->Subscribe<CollisionExitEvent>(this, &RenderBoxColliderSystem::OnCollidingExit);
		}

		virtual void RenderUpdate(float alpha) override
		{
			for (auto& entity : GetSystemEntities())
			{
				auto transform   = entity.GetComponent<TransformComponent>();
				auto boxCollider = entity.GetComponent<BoxColliderComponent>();

				// Interpolate transform position and rotation
				glm::vec2 renderPos = glm::mix(transform->PrevPosition, transform->Position, alpha);

				// Interpolate camera position (assume Camera() returns current camera with x,y and prevX, prevY set)
				auto camera = Application::Get().GetMainCamera();
				float camX  = camera->PrevX + alpha * (camera->X - camera->PrevX);
				float camY  = camera->PrevY + alpha * (camera->Y - camera->PrevY);

				float xPos = renderPos.x + boxCollider->Offset.x;
				float yPos = renderPos.y + boxCollider->Offset.y;

				SDL_Rect colliderRect {
					static_cast<int>(std::round(xPos - camX)),
					static_cast<int>(std::round(yPos - camY)),
					static_cast<int>(std::round(boxCollider->Width)),
					static_cast<int>(std::round(boxCollider->Height))
				};

				//TODO: come back to this after implementing opengl renderer
				if (m_hasCollidedMap[entity.GetId()])
				{
					// SDL_SetRenderDrawColor(renderer, RedColour.r, RedColour.g, RedColour.b, RedColour.a);
					// SDL_RenderDrawRect(renderer, &colliderRect);
				}
				else
				{
					// SDL_SetRenderDrawColor(renderer, GreenColour.r, GreenColour.g, GreenColour.b, GreenColour.a);
					// SDL_RenderDrawRect(renderer, &colliderRect);
				}
			}
		}

	private:
		SDL_Colour boxColour   = { 0 };
		SDL_Colour RedColour   = { 0 };
		SDL_Colour GreenColour = { 0 };

		void OnCollidingEnter(CollisionEnterEvent& e)
		{
			m_hasCollidedMap[e.First.GetId()]  = true;
			m_hasCollidedMap[e.Second.GetId()] = true;
		}

		void OnCollidingExit(CollisionExitEvent& e)
		{
			m_hasCollidedMap[e.First.GetId()]  = false;
			m_hasCollidedMap[e.Second.GetId()] = false;
		}

		std::map<uint32_t, bool> m_hasCollidedMap;
	};
} // namespace cedar
