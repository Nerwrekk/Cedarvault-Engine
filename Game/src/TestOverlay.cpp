#include "TestOverlay.h"

void TestOverlay::OnEvent(cedar::IEvent& event)
{
	CEDAR_INFO("OnEvent for: {}", GetTypeName());
}