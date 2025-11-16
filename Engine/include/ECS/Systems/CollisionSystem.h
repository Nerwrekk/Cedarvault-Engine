#pragma once

#include "Common/SDL_Wrapper.h"
#include "ECS/Components/Components.h"
#include "Common/Event/Events/Events.h"
#include "Common/Event/EventBus.h"

#include <map>
#include <utility>

namespace cedar
{
	class CollisionSystem : public BaseSystem
	{
	public:
		DECL_TYPE_NAME(CollisionSystem);

		CollisionSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<BoxColliderComponent>();

			// EventBus::Inst()->Subscribe<CollisionEnterEvent>(this, &CollisionSystem::TestingCollisionEnterEvent);
			// EventBus::Inst()->Subscribe<CollisionExitEvent>(this, &CollisionSystem::TestingCollisionExitEvent);
		}

		void TestingCollisionEnterEvent(CollisionEnterEvent& e)
		{
			CEDAR_INFO("Collision Enter triggerd with entity: {} and entity: {}", e.First.GetId(), e.Second.GetId());
		}

		void TestingCollisionExitEvent(CollisionExitEvent& e)
		{
			CEDAR_WARN("Collision Exit triggerd with entity: {} and entity: {}", e.First.GetId(), e.Second.GetId());
		}

		virtual void FixedUpdate(float fixedDeltaTime) override
		{
			UNREFERENCED_PARAMETER(fixedDeltaTime);

			auto entities = GetSystemEntities();

			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				auto entity1      = *it;
				auto transComp1   = entity1.GetComponent<TransformComponent>();
				auto boxCollComp1 = entity1.GetComponent<BoxColliderComponent>();
				for (auto jt = (it + 1); jt != entities.end(); jt++)
				{
					auto entity2 = *jt;

					auto collidedPair = std::make_pair(entity1.GetId(), entity2.GetId());

					auto transComp2   = entity2.GetComponent<TransformComponent>();
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
						m_onCollisionEnterMap[collidedPair] = true;

						//Check if they were not colliding previous frame
						if (m_prevOnCollisionEnterMap[collidedPair] == false)
						{
							EventBus::Inst()->PostEvent<CollisionEnterEvent>(entity1, entity2);
						}

						// entity2.Kill();
						EventBus::Inst()->PostEvent<CollisionEvent>(entity1, entity2);
					}
					else
					{
						//Check if they were colliding previous frame
						if (m_onCollisionEnterMap[collidedPair] == false && m_prevOnCollisionEnterMap[collidedPair] == true)
						{
							EventBus::Inst()->PostEvent<CollisionExitEvent>(entity1, entity2);
						}
					}
				}
			}

			m_prevOnCollisionEnterMap = m_onCollisionEnterMap;
			m_onCollisionEnterMap.clear();
		}

	private:
		//using pair so i can check specifically if two entieties had collided the previous turn
		//<<Entity id, Entity id>, hasCollided>
		std::map<std::pair<uint32_t, uint32_t>, bool> m_onCollisionEnterMap;
		std::map<std::pair<uint32_t, uint32_t>, bool> m_prevOnCollisionEnterMap;
	};
} // namespace cedar
