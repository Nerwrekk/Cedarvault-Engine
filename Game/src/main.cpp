#include "CedarVault.h"

void test(cedar::CollisionEvent& collevent)
{
	static int timesCalled = 0;
	CEDAR_WARN("Times called: {}", ++timesCalled);
	CEDAR_WARN("TEST: entity: {} collided with entity: {}", collevent.First.GetId(), collevent.Second.GetId());
}

void testKeyboard(cedar::KeyPressEvent& e)
{
	CEDAR_WARN("Key pressed: {}", e.Key);
}

int main()
{
	cedar::Application app;
	Mean::MeanScript::InitManagedScriptEngine("");
	Mean::MeanScript::LoadScriptAssembly("./TankGame.dll");
	// app.GetScriptEngine()->LoadScripts("./assets/scripts");
	// app.GetScriptEngine()->CallFunction("", "");

	cedar::AssetManager assetManager(app.GetRenderer());
	assetManager.LoadAssets("./assets/images");
	assetManager.LoadTilemaps("./assets/tilemaps");
	assetManager.LoadConfigurations("./assets/configurations");
	assetManager.LoadLevel("JungleLevel", 0);

	cedar::EventBus::Inst()->Subscribe<cedar::CollisionEvent>(&::test);
	cedar::EventBus::Inst()->Subscribe<cedar::KeyPressEvent>(&::testKeyboard);
	cedar::EventBus::Inst()->Unsubscribe<cedar::CollisionEvent>(&::test);
	app.Setup([&]()
	{
		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, -5.f));
		tank.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
		tank.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		tank.GetComponent<cedar::TransformComponent>()->Position = { 100, 400 };

		auto truck = app.Manager()->CreateEntity();
		// truck.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
		truck.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
		truck.GetComponent<cedar::TransformComponent>()->Position = { 0, 10 };
		truck.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
		truck.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Tank" });
		truck.AddComponent<cedar::CameraFollowComponent>();

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				auto tree = app.Manager()->CreateEntity();
				tree.AddComponent<cedar::RigidBodyComponent>(glm::vec2(-5.f * (i * 0.5), 0.f));
				tree.AddComponent<cedar::SpriteComponent>("tree", 32, 32, 0);
				tree.GetComponent<cedar::TransformComponent>()->Position = { 100 * (1 + i), 60 * (1 + j) };
				tree.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
			}
		}

		auto chopper = app.Manager()->CreateEntity();
		chopper.AddComponent<cedar::SpriteComponent>("chopper-spritesheet", 32, 32, 1);
		chopper.AddComponent<cedar::AnimationComponent>(2, 10, true);
		chopper.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		chopper.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Chopper" });
		// chopper.AddComponent<cedar::RigidBodyComponent>(glm::vec2(50.f, 0.f));
		// chopper.GetComponent<cedar::TransformComponent>()->Position = { 100, 440 };
	});

	app.Run();

	return 0;
}