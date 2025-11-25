#include "Application/Overlay.h"

namespace cedar
{
	void Overlay::OnAttach() {};
	void Overlay::OnDetach() {};

	void Overlay::OnEvent(IEvent& event)
	{
		UNREFERENCED_PARAMETER(event);
	};

	void Overlay::OnFixedUpdate(float fixedeltaTime)
	{
		UNREFERENCED_PARAMETER(fixedeltaTime);
	};

	void Overlay::OnUpdate(float deltaTime)
	{
		UNREFERENCED_PARAMETER(deltaTime);
	};

	void Overlay::OnRender(float alpha)
	{
		UNREFERENCED_PARAMETER(alpha);
	};

	void Overlay::OnImGuiRender() {};
} // namespace cedar
