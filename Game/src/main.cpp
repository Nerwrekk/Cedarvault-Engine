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

class FirstLayer : public cedar::Layer
{
public:
	DECL_TYPE_NAME(FirstLayer);

	void OnUpdate() override
	{
		// if (Mean::Input::IsMouseButtonPressed(Mean::Mouse::ButtonLeft))
		// {
		// 	MEAN_TRACE("Left mouse button pressed!");
		// }

		// auto mousePos = Mean::Input::GetMousePosition();
		// if (Mean::Input::IsMouseButtonPressed(Mean::Mouse::ButtonRight))
		// {
		// 	MEAN_TRACE("Mouse x:{} y:{}", mousePos.x, mousePos.y);
		// }

		// if (Mean::Input::IsMouseButtonPressed(Mean::Mouse::ButtonMiddle))
		// {
		// 	MEAN_TRACE("Mouse x:{} y:{}", Mean::Input::GetMouseX(), Mean::Input::GetMouseY());
		// }

		// if (Mean::Input::IsKeyPressed(Mean::Key::A))
		// {
		// 	MEAN_TRACE("A button pressed!");
		// }
	}

	// void OnAttach() override
	// {
	// 	AttachCallback<Mean::MouseMoveEvent>([this](Mean::MouseMoveEvent e)
	// 	{
	// 		MEAN_TRACE("Mouse x:{} y:{}", e.TargetX, e.TargetY);
	// 	});

	// 	AttachCallback<Mean::MouseDownEvent>([this](Mean::MouseDownEvent e)
	// 	{
	// 		MEAN_TRACE("Event: {}  Key: {}", e.GetName(), e.Button);
	// 	});

	// 	AttachCallback<Mean::MouseReleaseEvent>([this](Mean::MouseReleaseEvent e)
	// 	{
	// 		MEAN_TRACE("Event: {}  Key: {}", e.GetName(), e.Button);
	// 	});

	// 	AttachCallback<Mean::MouseMoveEvent>([this](Mean::MouseMoveEvent e)
	// 	{
	// 		MEAN_TRACE("Mouse x:{} y:{}", e.TargetX, e.TargetY);
	// 	});

	// 	AttachCallback<Mean::KeyPressEvent>([this](Mean::KeyPressEvent e)
	// 	{
	// 		MEAN_TRACE("Event: {}  Key: {}", e.GetName(), e.Key);
	// 	});

	// 	AttachCallback<Mean::KeyReleaseEvent>([this](Mean::KeyReleaseEvent e)
	// 	{
	// 		MEAN_TRACE("Event: {}  Key: {}", e.GetName(), e.Key);
	// 	});

	// 	AttachCallback<Mean::KeyRepeatEvent>([this](Mean::KeyRepeatEvent e)
	// 	{
	// 		MEAN_TRACE("Event: {}  Key: {}", e.GetName(), e.Key);
	// 	});
	// }

	void OnDetach() override
	{
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("MyWindow");
		ImGui::Checkbox("Boolean property", &this->someBool);
		if (ImGui::Button("Reset Speed"))
		{
			// This code is executed when the user clicks the button
			this->speed = 0;
		}
		ImGui::SliderFloat("Speed", &this->speed, 0.0f, 10.0f);
		ImGui::End();
	}

private:
	float speed;
	bool someBool;
};

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
				tree.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
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

	app.PushLayer<FirstLayer>();

	app.Run();

	return 0;
}