#pragma once

#include "CedarVault.h"

class GameLayer : public cedar::Layer
{
public:
	DECL_TYPE_NAME(GameLayer);

	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(cedar::IEvent& event) override;

	virtual void OnFixedUpdate(float fixedeltaTime) override;

	virtual void OnRender(float alpha) override; // for interpolation
	virtual void OnImGuiRender() override;

private:
	float speed      = 0;
	bool pausedState = false;
};