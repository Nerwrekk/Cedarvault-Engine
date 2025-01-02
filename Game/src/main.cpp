#include "CedarVault.h"

#include <iostream>

int main()
{
	CEDAR_INFO("Hello World!");
	cedar::Entity entity = cedar::EntityManager::Instance()->CreateEntity();
	cedar::EntityManager::Instance()->AddComponent<cedar::TransformComponent>(entity, glm::vec2(10, 190), glm::vec2(10, 10), 360);
	if (cedar::EntityManager::Instance()->HasComponent<cedar::TransformComponent>(entity))
	{
		CEDAR_DEBUG("Entity with id: {} has TransformComponent", entity.GetId());
	}
	cedar::EntityManager::Instance()->RemoveComponent<cedar::TransformComponent>(entity);
	cedar::EntityManager::Instance()->AddSystem<cedar::MovementSystem>();
	cedar::EntityManager::Instance()->AddSystem<cedar::MovementSystem>();
	cedar::Application app;
	app.Run();
}