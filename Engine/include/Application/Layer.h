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
		template <typename TEvent, typename TOwner>
		void Subscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&))
		{
			EventBus::Inst()->Subscribe<TEvent>(owner, memberCallbackFunction);
		}

		template <typename TEvent>
		void Subscribe(void (*freeCallbackFunction)(TEvent&))
		{
			EventBus::Inst()->Subscribe<TEvent>(freeCallbackFunction);
		}

		template <typename TEvent, typename TOwner>
		void Unsubscribe(TOwner* owner, void (TOwner::*memberCallbackFunction)(TEvent&))
		{
			EventBus::Inst()->Unsubscribe<TEvent>(owner, memberCallbackFunction);
		}

		template <typename TEvent>
		void Unsubscribe(void (*freeCallbackFunction)(TEvent&))
		{
			EventBus::Inst()->Unsubscribe<TEvent>(freeCallbackFunction);
		}

		template <typename Event, typename... Args>
		void PostEvent(Args&&... args)
		{
			EventBus::Inst()->PostEvent<Event>(std::forward<Args>(args)...);
		}

		template <typename Task>
		void PostTask(Task&& task)
		{
			EventBus::Inst()->PostTask(std::move(task));
		}

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnFixedUpdate(float fixedeltaTime)
		{
			UNREFERENCED_PARAMETER(fixedeltaTime);
		};
		virtual void OnUpdate(float deltaTime)
		{
			UNREFERENCED_PARAMETER(deltaTime);
		};
		virtual void OnRender(float alpha)
		{
			UNREFERENCED_PARAMETER(alpha);
		}; // for interpolation
		virtual void OnImGuiRender() {};

	protected:
		friend class LayerStack;
		uint32_t m_layerID;
	};

}