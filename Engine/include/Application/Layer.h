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

		template <typename TLayer> //Layer is derived from Layerbase
		TLayer* GetLayer()
		{
			CEDAR_STATIC_ASSERT(std::is_base_of<Layer, TLayer>::value);

			auto iterator = std::find_if(m_context->layers.begin(), m_context->layers.end(), [this](auto layer)
			{
				return (layer->m_layerID == TypeIdOf<TLayer>());
			});

			if (iterator != m_context->layers.end())
			{
				return static_cast<TLayer*>(*iterator);
			}

			return nullptr;
		}

	public:
		//We are leveraging variable template here '...' to be able to attach new layers that have multiple
		//arguments in their constructor
		template <typename TLayer, typename... Args>
		TLayer* AttachLayer(Args&&... args)
		{
			//check layers type compliance
			CEDAR_STATIC_ASSERT(std::is_base_of<Layer, TLayer>::value);

			//check if layers already exists
			if (GetLayer<TLayer>() != nullptr)
			{
				CEDAR_ERROR("Layers already attached!");

				return nullptr;
			}

			//create layer and add to collection
			auto layer = new TLayer(std::forward<Args>(args)...);
			m_context->layers.push_back(layer);
			layer->m_layerID = TypeIdOf<TLayer>();
			layer->m_context = this->m_context;
			layer->OnAttach();

			return layer;
		}

		template <typename TLayer>
		void DetachLayer()
		{
			CEDAR_STATIC_ASSERT(std::is_base_of<Layer, TLayer>::value);

			EventBus::Inst()->PostTask([this]()
			{
				m_context->layers.erase(std::remove_if(
				                            m_context->layers.begin(),
				                            m_context->layers.end(),
				                            [this](auto& layer)
				{
					if (layer->m_layerID == TypeID<TLayer>())
					{
						layer->OnDetach();
						EventBus::Inst()->EraseListener(layer->m_layerID);
						MEAN_DELETE(layer);

						return true;
					}

					return false;
				}),
				    m_context->layers.end());
			});
		}

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

		template <typename Event>
		void DetachCallback()
		{
			EventBus::Inst()->DetachCallback<Event>(this->m_layerID);
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

	protected:
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};

		friend class AppLayer;
		friend class AppContext;
		AppContext* m_context;
		uint64_t m_layerID;
	};
}