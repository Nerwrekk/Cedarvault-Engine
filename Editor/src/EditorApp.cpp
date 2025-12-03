#include "CedarVault.h"
#include "Common/EntryPoint.h"
#include "EditorLayer.h"

class EditorApp : public cedar::Application
{
public:
	EditorApp()
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
		scene->PushLayer<cedar::EditorLayer>();

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

		auto chopper = scene->CreateEntity();
		chopper.AddComponent<cedar::SpriteComponent>("chopper-spritesheet", 32, 32, 1);
		chopper.AddComponent<cedar::AnimationComponent>(2, 10, true);
		chopper.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		chopper.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Chopper" });
	}

	~EditorApp()
	{
	}
};

cedar::Application* cedar::CreateApplication()
{
	return new EditorApp();
}