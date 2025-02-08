#include "CedarVault.h"

#include <iostream>

int main()
{
	cedar::Application app;

	cedar::AssetManager assetManager(app.GetRenderer());
	assetManager.LoadAssets("./assets/images");
	assetManager.LoadTilemaps("./assets/tilemaps");
	assetManager.LoadConfigurations("./assets/configurations");

	//TODO: Make it so Application loads in the correct level!
	// assetManager.LoadLevel("jungle", "jungle");

	app.Setup([&]()
	{
		auto chopper = app.Manager()->CreateEntity();
		chopper.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 1.f));
		chopper.AddComponent<cedar::SpriteComponent>("chopper", 32, 32, 1);
		chopper.AddComponent<cedar::AnimationComponent>(2, 10, true);
		chopper.GetComponent<cedar::TransformComponent>()->Position = { 10, 200 };

		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, -10.f));
		tank.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
		tank.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		tank.GetComponent<cedar::TransformComponent>()->Position = { 10, 200 };

		auto truck = app.Manager()->CreateEntity();
		truck.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
		truck.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
		truck.GetComponent<cedar::TransformComponent>()->Position = { 0, 10 };
		truck.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
	});

	app.Run();

	return 0;
}