#include "CedarVault.h"

#include <sol/sol.hpp>

void TestLua()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script_file("./assets/scripts/testLua.lua");

	int someVariable = lua["Some_variable"];

	bool isFullScreen = lua["Config"]["fullscreen"];

	sol::table config = lua["Config"];

	CEDAR_WARN("someVariable is: {}", someVariable);
}

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

#define __NETHOST_H__

int main()
{
	Mean::MeanScript::Init();
	cedar::Application app;
	app.GetScriptEngine()->LoadScripts("./assets/scripts");
	app.GetScriptEngine()->CallFunction("", "");

	cedar::AssetManager assetManager(app.GetRenderer());
	assetManager.LoadAssets("./assets/images");
	assetManager.LoadTilemaps("./assets/tilemaps");
	assetManager.LoadConfigurations("./assets/configurations");

	//TODO: Make it so Application loads in the correct level!
	// assetManager.LoadLevel("jungle", "jungle");
	// cedar::EventBus::Inst()->Subscribe<cedar::CollisionEvent>(&::test);
	// cedar::EventBus::Inst()->Subscribe<cedar::KeyPressEvent>(&::testKeyboard);
	// cedar::EventBus::Inst()->Unsubscribe<cedar::CollisionEvent>(&::test);
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
		truck.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Tank" });

		for (int i = 0; i < 5; i++)
		{
			auto tree = app.Manager()->CreateEntity();
			tree.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
			tree.AddComponent<cedar::SpriteComponent>("tree", 32, 32, 0);
			tree.GetComponent<cedar::TransformComponent>()->Position = { 100, 60 * (1 + i) };
			tree.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
		}

		auto chopper = app.Manager()->CreateEntity();
		chopper.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
		chopper.AddComponent<cedar::SpriteComponent>("chopper", 32, 32, 1);
		chopper.AddComponent<cedar::AnimationComponent>(2, 10, true);
		chopper.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		chopper.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Chopper" });
		chopper.GetComponent<cedar::TransformComponent>()->Position = { 100, 440 };
	});

	app.Run();

	return 0;
}