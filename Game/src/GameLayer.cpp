#include "GameLayer.h"

GameLayer::GameLayer(SDL_Renderer* renderer, cedar::RenderSystem* renderSystem, cedar::EntityManager* entityManager)
{
	p_renderer      = renderer;
	p_renderSystem  = renderSystem;
	p_entityManager = entityManager;
}

static void testMouse(cedar::MouseMoveEvent& e)
{
	CEDAR_WARN("Mouse moved, X: {}, Y: {}", e.TargetX, e.TargetY);
}

static void testMouseClick(cedar::MouseDownEvent& e)
{
	CEDAR_WARN("Mouse button clicked: {}", e.Button);
}

static void testMouseRelease(cedar::MouseReleaseEvent& e)
{
	CEDAR_WARN("Mouse button released: {}", e.Button);
}

void GameLayer::OnAttach()
{
	// cedar::EventBus::Inst()->Subscribe<cedar::MouseMoveEvent>(&::testMouse);
	cedar::EventBus::Inst()->Subscribe<cedar::MouseDownEvent>(&::testMouseClick);
	cedar::EventBus::Inst()->Subscribe<cedar::MouseReleaseEvent>(&::testMouseRelease);

	auto tank = p_entityManager->CreateEntity();
	tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, -5.f));
	tank.AddComponent<cedar::SpriteComponent>("tank-panther-right", 32, 32, 0);
	tank.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
	tank.GetComponent<cedar::TransformComponent>()->Position = { 100, 400 };

	auto truck = p_entityManager->CreateEntity();
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
			auto tree = p_entityManager->CreateEntity();
			tree.AddComponent<cedar::RigidBodyComponent>(glm::vec2(0.f, 0.f));
			tree.AddComponent<cedar::SpriteComponent>("tree", 32, 32, 0);
			tree.GetComponent<cedar::TransformComponent>()->Position = { 100 * (1 + i), 60 * (1 + j) };
			tree.AddComponent<cedar::BoxColliderComponent>(32, 32, glm::vec2(0, 0));
		}
	}

	auto chopper = p_entityManager->CreateEntity();
	chopper.AddComponent<cedar::SpriteComponent>("chopper-spritesheet", 32, 32, 1);
	chopper.AddComponent<cedar::AnimationComponent>(2, 10, true);
	chopper.AddComponent<cedar::BoxColliderComponent>(20, 18, glm::vec2(4, 8));
	chopper.AddComponent<cedar::ScriptComponent>(std::vector<std::string> { "Chopper" });
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnEvent(cedar::IEvent& event)
{
	//TODO: REMOVE THIS WHEN DONE TESTING
	event.Handled = true;
}

void GameLayer::OnFixedUpdate(float fixedeltaTime)
{
	if (cedar::Input::IsMouseButtonPressed(cedar::Mouse::MB_Left))
	{
		CEDAR_INFO("Left mouse button clicked");
	}

	if (cedar::Input::IsMouseButtonReleased(cedar::Mouse::MB_Left))
	{
		CEDAR_INFO("Left mouse button released");
	}

	if (cedar::Input::IsMouseButtonDown(cedar::Mouse::MB_Right))
	{
		CEDAR_INFO("Right mouse button held down");
	}

	// auto mousePos = cedar::Input::GetMousePosition();
	// CEDAR_ERROR("Mouse pos: X: {}, Y: {}", mousePos.x, mousePos.y);
	// process queued events (from input -> event bus)
	// m_eventBus->PollEvents();
	//TODO: maybe look into putting this into the main game loop instead
	// p_entityManager->SnapshotPreviousState();

	p_entityManager->FixedUpdateAllSystems(fixedeltaTime);

	p_entityManager->LateUpdateAllSystems();

	//TODO: maybe look into putting this into the main game loop instead
	// p_entityManager->Update(); //treat it as FlushCommandBuffers
}

void GameLayer::OnRender(float alpha)
{
	SDL_SetRenderDrawColor(p_renderer, 21, 21, 21, 255);
	SDL_RenderClear(p_renderer);

	//TODO: TEMPORARY, remember to fix!
	cedar::Application::Get().RenderCurrentLevel(cedar::Application::Get().GameSetting.CurrentLevel,
	    cedar::Application::Get().GameSetting.CurrentLevelIndex);

	p_renderSystem->RenderEntites(p_renderer, alpha);

	p_entityManager->RenderUpdateAllSystems(p_renderer, alpha);
}

void GameLayer::OnImGuiRender()
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
