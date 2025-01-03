#include "CedarVault.h"

#include <iostream>

int main()
{
	cedar::Application app;
	app.Setup([&]()
	{
		auto entity = app.Manager().CreateEntity();

		auto T = cedar::EntityManager::Instance()->GetSystem<cedar::MovementSystem>();
		if (T)
		{
			CEDAR_INFO("T is not null");
		}
	});

	app.Run();

	return 0;
}