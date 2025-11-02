#pragma once

#include "Common/SDL_Wrapper.h"
#include "ECS/Components/Components.h"
#include "Common/Event/Events/Events.h"
#include "Common/Event/EventBus.h"

#include <map>

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

			EventBus::Inst()->Subscribe<CollisionEnterEvent>(this, &CollisionSystem::TestingCollisionEnterEvent);
			EventBus::Inst()->Subscribe<CollisionExitEvent>(this, &CollisionSystem::TestingCollisionExitEvent);
		}

		void TestingCollisionEnterEvent(CollisionEnterEvent& e)
		{
			CEDAR_INFO("Collision Enter triggerd with entity: {} and entity: {}", e.First.GetId(), e.Second.GetId());
		}

		void TestingCollisionExitEvent(CollisionExitEvent& e)
		{
			CEDAR_INFO("Collision Exit triggerd with entity: {} and entity: {}", e.First.GetId(), e.Second.GetId());
		}

		virtual void Update() override
		{
			auto entities = GetSystemEntities();
			for (auto& entity : entities)
			{
				m_onCollisionEnterMap[entity.GetId()] = false;
			}

			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				auto entity1      = *it;
				auto transComp1   = entity1.GetComponent<TransformComponent>();
				auto boxCollComp1 = entity1.GetComponent<BoxColliderComponent>();
				for (auto jt = (it + 1); jt != entities.end(); jt++)
				{
					auto entity2      = *jt;
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
						m_onCollisionEnterMap[entity1.GetId()] = true;
						m_onCollisionEnterMap[entity2.GetId()] = true;

						if (m_prevOnCollisionEnterMap[entity1.GetId()] == false &&
						    m_prevOnCollisionEnterMap[entity2.GetId()] == false)
						{
							EventBus::Inst()->PostEvent<CollisionEnterEvent>(entity1, entity2);
						}

						// entity2.Kill();
						EventBus::Inst()->PostEvent<CollisionEvent>(entity1, entity2);
					}
					else
					{
						if (m_onCollisionEnterMap[entity1.GetId()] == false && m_prevOnCollisionEnterMap[entity1.GetId()] == true &&
						    m_onCollisionEnterMap[entity2.GetId()] == false && m_prevOnCollisionEnterMap[entity2.GetId()] == true)
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
		std::map<uint32_t, bool> m_onCollisionEnterMap;
		std::map<uint32_t, bool> m_prevOnCollisionEnterMap;
	};
} // namespace cedar
