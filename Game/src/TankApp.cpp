#include "CedarVault.h"
#include "Common/EntryPoint.h"
#include "GameLayer.h"

class TankApp : public cedar::Application
{
public:
	TankApp()
	{
		Mean::MeanScript::InitManagedScriptEngine("");
		Mean::MeanScript::LoadScriptAssembly("./TankGame.dll");
		// GetScriptEngine()->LoadScripts("./assets/scripts");
		// GetScriptEngine()->CallFunction("", "");

		m_assetManager->LoadAssets("./assets/images");
		m_assetManager->LoadTilemaps("./assets/tilemaps");
		m_assetManager->LoadConfigurations("./assets/configurations");
		m_assetManager->LoadLevel("JungleLevel", 0);

		//TODO: temporary solution, will fix later when scenes are established
		PushLayer<GameLayer>(m_renderer, m_renderSystem.get(), m_entityManager.get());
	}

	~TankApp()
	{
	}
};

cedar::Application* cedar::CreateApplication()
{
	return new TankApp();
}