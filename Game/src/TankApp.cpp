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

		//TODO: temporary solution, will fix later when scenes are established
		auto scene = cedar::SceneManager::Get()->CreateScene("DefaultScene");
		scene->PushLayer<GameLayer>(m_renderer, scene->GetEntityRegister()->GetSystem<cedar::RenderSystem>().get(), scene->GetEntityRegister());
		// PushLayer<GameLayer>(m_renderer, m_renderSystem.get(), m_entityManager.get());
		scene->PushLayer<TestOverlay>();
		cedar::SceneManager::Get()->SetActiveScene(scene);
		// PushLayer<TestOverlay>();
	}

	~TankApp()
	{
	}
};

cedar::Application* cedar::CreateApplication()
{
	return new TankApp();
}