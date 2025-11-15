#pragma once

#include "CedarVault.h"

class GameLayer : public cedar::Layer
{
public:
	DECL_TYPE_NAME(GameLayer);

	GameLayer(SDL_Renderer* renderer, cedar::RenderSystem* renderSystem, cedar::EntityManager* entityManager);
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnFixedUpdate(float fixedeltaTime) override;

	virtual void OnRender(float alpha) override; // for interpolation
	virtual void OnImGuiRender() override;

private:
	//TODO: temporary solution, will fix later when scenes are established
	SDL_Renderer* p_renderer;
	cedar::RenderSystem* p_renderSystem;
	cedar::EntityManager* p_entityManager;

	float speed   = 0;
	bool someBool = false;
};