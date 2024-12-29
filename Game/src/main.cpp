#include "CedarVault.h"

#include <iostream>

int main()
{
	CEDAR_INFO("Hello World!");
	cedar::Entity entity = cedar::EntityManager::Instance()->CreateEntity();
	cedar::EntityManager::Instance()->AddComponent<cedar::TransformComponent>(entity, glm::vec2(10, 190), glm::vec2(10, 10), 360);
	cedar::EntityManager::Instance()->RemoveComponent<cedar::TransformComponent>(entity);
	cedar::Application app;
	app.Run();
}