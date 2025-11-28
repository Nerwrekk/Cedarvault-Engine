#include "CedarVault.h"
#include "Common/EntryPoint.h"
#include "GameLayer.h"
#include "TestOverlay.h"

class TankApp : public cedar::Application
{
public:
	TankApp()
	{
		Mean::MeanScript::InitManagedScriptEngine("");
		Mean::MeanScript::LoadScriptAssembly("./TankGame.dll");
		// GetScriptEngine()->LoadScripts("./assets/scripts");

		m_assetManager->LoadAssets("./assets/images");
		m_assetManager->LoadTilemaps("./assets/tilemaps");
		m_assetManager->LoadConfigurations("./assets/configurations");
		m_assetManager->LoadLevel("JungleLevel", 0);

		auto scene = cedar::SceneManager::Get()->CreateScene("DefaultScene");
		cedar::SceneManager::Get()->SetActiveScene(scene);
		scene->PushLayer<GameLayer>();
		scene->PushLayer<TestOverlay>();

		SetupEntities(scene);
	}

	//TODO: Temporary until the editior is implemented
	void SetupEntities(cedar::Scene* scene)
	{
		auto tank = scene->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, -5.f));
		tank.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
		tank.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		tank.GetComponent<cedar::TransformComponent>()->Position = { 100, 400 };

		auto truck = scene->CreateEntity();
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
				auto tree = scene->CreateEntity();
				tree.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
				tree.AddComponent<cedar::SpriteComponent>("tree", 32, 32, 0);
				tree.GetComponent<cedar::TransformComponent>()->Position = { 100 * (1 + i), 60 * (1 + j) };
				tree.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
			}
		}

		auto chopper = scene->CreateEntity();
		chopper.AddComponent<cedar::SpriteComponent>("chopper-spritesheet", 32, 32, 1);
		chopper.AddComponent<cedar::AnimationComponent>(2, 10, true);
		chopper.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		chopper.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Chopper" });
	}

	~TankApp()
	{
	}
};

cedar::Application* cedar::CreateApplication()
{
	return new TankApp();
}