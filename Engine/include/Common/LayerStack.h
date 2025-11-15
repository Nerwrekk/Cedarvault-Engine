#pragma once

#include "Application/Layer.h"
#include "Registry/TypeRegistry.h"

namespace cedar
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void Clear();

		template <typename TLayer, typename... Args>
		TLayer* PushLayer(Args&&... args);

		template <typename TLayer>
		void PopLayer();

		template <typename TLayer> //Layer is derived from Layerbase
		TLayer* GetLayer();

		//TODO: maybe add theese later
		// void PushOverlay(Layer* overlay);
		// void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin()
		{
			return m_layers.begin();
		}
		std::vector<Layer*>::iterator end()
		{
			return m_layers.end();
		}
		std::vector<Layer*>::reverse_iterator rbegin()
		{
			return m_layers.rbegin();
		}
		std::vector<Layer*>::reverse_iterator rend()
		{
			return m_layers.rend();
		}

		std::vector<Layer*>::const_iterator begin() const
		{
			return m_layers.begin();
		}
		std::vector<Layer*>::const_iterator end() const
		{
			return m_layers.end();
		}
		std::vector<Layer*>::const_reverse_iterator rbegin() const
		{
			return m_layers.rbegin();
		}
		std::vector<Layer*>::const_reverse_iterator rend() const
		{
			return m_layers.rend();
		}

	private:
		std::vector<Layer*> m_layers;
		// unsigned int m_LayerInsertIndex = 0;
	};

	//We are leveraging variable template here '...' to be able to attach new layers that have multiple
	//arguments in their constructor
	template <typename TLayer, typename... Args>
	TLayer* LayerStack::PushLayer(Args&&... args)
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
		m_layers.push_back(layer);
		layer->m_layerID = TypeIdOf<TLayer>();
		layer->OnAttach();

		return layer;
	}

	template <typename TLayer>
	void LayerStack::PopLayer()
	{
		CEDAR_STATIC_ASSERT(std::is_base_of<Layer, TLayer>::value);

		EventBus::Inst()->PostTask([this]()
		{
			m_layers.erase(std::remove_if(
			                   m_layers.begin(),
			                   m_layers.end(),
			                   [this](auto& layer)
			{
				if (layer->m_layerID == TypeIdOf<TLayer>())
				{
					layer->OnDetach();
					CEDAR_DELETE(layer);

					return true;
				}

				return false;
			}),
			    m_layers.end());
		});
	}

	template <typename TLayer> //Layer is derived from Layerbase
	TLayer* LayerStack::GetLayer()
	{
		CEDAR_STATIC_ASSERT(std::is_base_of<Layer, TLayer>::value);

		auto iterator = std::find_if(m_layers.begin(), m_layers.end(), [this](auto layer)
		{
			return (layer->m_layerID == TypeIdOf<TLayer>());
		});

		if (iterator != m_layers.end())
		{
			return static_cast<TLayer*>(*iterator);
		}

		return nullptr;
	}
} // namespace cedar
