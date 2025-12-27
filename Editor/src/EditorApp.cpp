#include "CedarVault.h"
#include "Common/EntryPoint.h"
#include "EditorLayer.h"
#include "OpenGlLayer.h"

class EditorApp : public cedar::Application
{
public:
	EditorApp()
	{
		SetAppMode(cedar::AppMode::Editor);

		Mean::MeanScript::InitManagedScriptEngine("");
		Mean::MeanScript::LoadScriptAssembly("../bin/TankGame.dll");
		// GetScriptEngine()->LoadScripts("./assets/scripts");

		// m_assetManager->LoadAssets("../assets/images");
		// m_assetManager->LoadTilemaps("../assets/tilemaps");
		// m_assetManager->LoadConfigurations("../assets/configurations");
		// m_assetManager->LoadLevel("JungleLevel", 0);

		PushLayer<cedar::EditorLayer>();
		PushLayer<cedar::OpenGlLayer>();

		auto scene = cedar::SceneManager::Get()->CreateScene("DefaultScene");
		cedar::SceneManager::Get()->SetActiveScene(scene);

		SetupEntities(scene);
	}

	//TODO: Temporary until the editior is implemented
	void SetupEntities(cedar::Scene* scene)
	{
		auto tank = scene->CreateEntity();
		// tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, -5.f));
		tank.AddComponent<cedar::SpriteComponent>("eye_strip");
		tank.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		tank.AddComponent<cedar::AnimationComponent>(34, 4, true);
		tank.GetComponent<cedar::TransformComponent>()->Position = { 400, 400 };
		tank.GetComponent<cedar::TransformComponent>()->Scale    = { 3, 3 };

		auto truck = scene->CreateEntity();
		// truck.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
		truck.AddComponent<cedar::SpriteComponent>("tank-panther-right");
		truck.GetComponent<cedar::TransformComponent>()->Position = { 0, 10 };
		truck.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
		truck.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Tank" });
		truck.AddComponent<cedar::CameraFollowComponent>();

		auto chopper = scene->CreateEntity();
		chopper.AddComponent<cedar::SpriteComponent>("player_walk_left_strip", 1);
		chopper.AddComponent<cedar::AnimationComponent>(4, 4, true);
		chopper.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
		chopper.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Chopper" });
		chopper.GetComponent<cedar::TransformComponent>()->Position = { 300, 500 };
		chopper.GetComponent<cedar::TransformComponent>()->Scale    = { 3, 3 };
	}

	~EditorApp()
	{
	}
};

cedar::Application* cedar::CreateApplication()
{
	return new EditorApp();
}