#pragma once

#include "Common/SDL_Wrapper.h"
#include "ECS/Components/Components.h"

namespace cedar
{
	class CollisionSystem : public BaseSystem
	{
	public:
		CollisionSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<BoxColliderComponent>();
		}

		virtual void Update(double deltaTime) override
		{
			auto entities = GetSystemEntities();
			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				auto entity1 = *it;
				auto transComp1 = entity1.GetComponent<TransformComponent>();
				auto boxCollComp1 = entity1.GetComponent<BoxColliderComponent>();
				for (auto jt = (it + 1); jt != entities.end(); jt++)
				{
					auto entity2 = *jt;
					auto transComp2 = entity2.GetComponent<TransformComponent>();
					auto boxCollComp2 = entity2.GetComponent<BoxColliderComponent>();

					auto entity1PosX = transComp1->Position.x + boxCollComp1->Offset.x;
					auto entity1PosY = transComp1->Position.y + boxCollComp1->Offset.y;

					auto entity2PosX = transComp2->Position.x + boxCollComp2->Offset.x;
					auto entity2PosY = transComp2->Position.y + boxCollComp2->Offset.y;
					//check collision
					if (entity1PosX < entity2PosX + boxCollComp2->Width &&
					    entity1PosX + boxCollComp1->Width > entity2PosX &&
					    entity1PosY < entity2PosY + boxCollComp2->Height &&
					    entity1PosY + boxCollComp1->Height > entity2PosY)
					{
						CEDAR_INFO("Collision Detected");
					}
				}
			}
		}
	};
} // namespace cedar
