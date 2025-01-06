#include "CedarVault.h"

#include <iostream>

int main()
{
	cedar::Application app;
	app.Setup([&]()
	{
		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(50.f, 0.f));
	});

	app.Run();

	return 0;
}