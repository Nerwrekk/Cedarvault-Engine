#pragma once

#include "Common/Event/EventBus.h"
#include "CedarAssert.h"
#include "Common/Core.h"
#include "Registry/TypeRegistry.h"

namespace cedar
{
	class Layer
	{
	public:
		virtual ~Layer() = default;

	public:
		virtual void OnAttach() {};
		virtual void OnDetach() {};

		virtual void OnEvent(IEvent& event)
		{
			UNREFERENCED_PARAMETER(event);
		};

		virtual void OnFixedUpdate(float fixedeltaTime)
		{
			UNREFERENCED_PARAMETER(fixedeltaTime);
		};

		virtual void OnUpdate(float deltaTime)
		{
			UNREFERENCED_PARAMETER(deltaTime);
		};

		virtual void OnRender(float alpha) // for interpolation
		{
			UNREFERENCED_PARAMETER(alpha);
		};

		virtual void OnImGuiRender() {};

	protected:
		friend class LayerStack;
		uint32_t m_layerID;
	};

}