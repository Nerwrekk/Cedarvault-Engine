#include "CedarVault.h"

#include <iostream>

int main()
{
	Mindi::json_node jungleTileMapNode;
	Mindi::json_reader::read("./assets/configurations/jungleConfig.json", &jungleTileMapNode);

	CEDAR_INFO("{}", jungleTileMapNode["name"].get_string());
	CEDAR_INFO("{}", jungleTileMapNode["tileSize"].get_int());
	CEDAR_INFO("{}", jungleTileMapNode["tileScale"].get_int());
	auto map = jungleTileMapNode["map"].get_array();
	for (auto& t : map)
	{
		CEDAR_INFO("{}", t->get_int());
	}

	cedar::Application app;

	cedar::AssetManager assetManager(app.GetRenderer());
	assetManager.LoadAssets("./assets/images");
	assetManager.LoadTilemaps("./assets/tilemaps");

	// assetManager.LoadLevel("jungle", "jungle");

	app.Setup([&]()
	{
		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(50.f, 0.f));
		tank.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32);

		auto truck = app.Manager()->CreateEntity();
		truck.AddComponent<cedar::RigidBodyComponent>(glm::vec2(30.f, -10.f));
		truck.AddComponent<cedar::SpriteComponent>("truck-ford-right", 32, 32);
		truck.GetComponent<cedar::TransformComponent>()->Position = { 400, 500 };
	});

	app.Run();

	return 0;
}