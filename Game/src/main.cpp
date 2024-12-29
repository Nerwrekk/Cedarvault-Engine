#include "CedarVault.h"

#include <iostream>

int main()
{
	CEDAR_INFO("Hello World!");
	cedar::Entity entity = cedar::EntityManager::Instance()->CreateEntity();
	cedar::Application app;
	app.Run();
}