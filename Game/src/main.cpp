#include "CedarVault.h"

#include <iostream>

int main()
{
	cedar::Application app;
	app.Setup([&]()
	{
		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(50.f, 0.f));
		tank.AddComponent<cedar::SpriteComponent>("./assets/images/tank-panther-right.png");
	});

	app.Run();

	return 0;
}