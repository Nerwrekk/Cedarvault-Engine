#include "GameLayer.h"

GameLayer::GameLayer()
{
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
	// cedar::EventBus::Inst()->Subscribe<cedar::MouseDownEvent>(&::testMouseClick);
	// cedar::EventBus::Inst()->Subscribe<cedar::MouseReleaseEvent>(&::testMouseRelease);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnEvent(cedar::IEvent& event)
{
	CEDAR_WARN("OnEvent for: {}", GetTypeName());
	//TODO: REMOVE THIS WHEN DONE TESTING
	// event.Handled = true;
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
}

void GameLayer::OnRender(float alpha)
{
	//TODO: TEMPORARY, remember to fix!
	cedar::Application::Get().RenderCurrentLevel(cedar::Application::Get().GameSetting.CurrentLevel,
	    cedar::Application::Get().GameSetting.CurrentLevelIndex);
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
