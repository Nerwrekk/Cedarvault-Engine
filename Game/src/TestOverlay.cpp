#include "TestOverlay.h"

void TestOverlay::OnEvent(cedar::IEvent& event)
{
	CEDAR_INFO("OnEvent for: {}", GetTypeName());
}

void TestOverlay::OnImGuiRender()
{
	ImGui::Begin("Entities");

	for (auto entity : cedar::SceneManager::Get()->GetActiveScene()->GetEntityRegister()->GetAllEntities())
	{
		ImGui::Text("Entity ID: %d", entity.GetId());
		std::string buttonLabel = "Kill Entity " + std::to_string(entity.GetId());
		if (ImGui::Button(buttonLabel.c_str()))
		{
			// This code is executed when the user clicks the button
			cedar::SceneManager::Get()->GetActiveScene()->GetEntityRegister()->KillEntity(entity);
		}
	}

	ImGui::End();
}