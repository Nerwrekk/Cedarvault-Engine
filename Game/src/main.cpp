#include "CedarVault.h"

#include <iostream>

int main()
{
	cedar::Application app;

	cedar::AssetManager assetManager(app.GetRenderer());
	assetManager.LoadAssets("./assets/imagess");

	app.Setup([&]()
	{
		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(50.f, 0.f));
		tank.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32);

		auto truck = app.Manager()->CreateEntity();
		truck.AddComponent<cedar::RigidBodyComponent>(glm::vec2(30.f, -10.f));
		truck.AddComponent<cedar::SpriteComponent>("truck-ford-right", 32, 32);
		truck.GetComponent<cedar::TransformComponent>()->Position = { 400, 500 };
	});

	app.Run();

	return 0;
}