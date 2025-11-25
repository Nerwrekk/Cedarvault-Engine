#pragma once

#include "Layer.h"

namespace cedar
{
	class Overlay : public Layer
	{
	public:
		virtual ~Overlay() = default;

	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnEvent(IEvent& event) override;
		virtual void OnFixedUpdate(float fixedeltaTime) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender(float alpha) override;
		virtual void OnImGuiRender() override;

		friend class LayerStack;
	};

}