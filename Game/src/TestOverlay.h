#pragma once

#include "CedarVault.h"

class TestOverlay : public cedar::Overlay
{
public:
	DECL_TYPE_NAME(TestOverlay);

	TestOverlay()          = default;
	virtual ~TestOverlay() = default;

	virtual void OnEvent(cedar::IEvent& event) override;
	virtual void OnImGuiRender() override;
};