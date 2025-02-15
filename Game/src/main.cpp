#include "CedarVault.h"

#include <iostream>

void test(cedar::CollisionEvent* collevent)
{
	CEDAR_WARN("TEST: entity: {} collided with entity: {}", collevent->First.GetId(), collevent->Second.GetId());
}

int main()
{
	cedar::EventBus eventbus;
	cedar::Application app;

	cedar::AssetManager assetManager(app.GetRenderer());
	assetManager.LoadAssets("./assets/images");
	assetManager.LoadTilemaps("./assets/tilemaps");
	assetManager.LoadConfigurations("./assets/configurations");

	//TODO: Make it so Application loads in the correct level!
	// assetManager.LoadLevel("jungle", "jungle");
	eventbus.Subscribe<cedar::CollisionEvent>(&::test);
	app.Setup([&]()
	{
		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, -5.f));
		tank.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
		tank.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		tank.GetComponent<cedar::TransformComponent>()->Position = { 100, 400 };

		auto truck = app.Manager()->CreateEntity();
		truck.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
		truck.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
		truck.GetComponent<cedar::TransformComponent>()->Position = { 0, 10 };
		truck.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));

		eventbus.EmitEvent<cedar::CollisionEvent>(&cedar::CollisionEvent(tank, truck));

		for (int i = 0; i < 5; i++)
		{
			auto tree = app.Manager()->CreateEntity();
			tree.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
			tree.AddComponent<cedar::SpriteComponent>("tree", 32, 32, 0);
			tree.GetComponent<cedar::TransformComponent>()->Position = { 100, 60 * (1 + i) };
			tree.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
		}

		auto chopper = app.Manager()->CreateEntity();
		chopper.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, -10.f));
		chopper.AddComponent<cedar::SpriteComponent>("chopper", 32, 32, 1);
		chopper.AddComponent<cedar::AnimationComponent>(2, 10, true);
		chopper.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		chopper.GetComponent<cedar::TransformComponent>()->Position = { 100, 440 };
	});

	app.Run();

	return 0;
}