#include "Common/LayerStack.h"

namespace cedar
{
	LayerStack::LayerStack()
	{
		m_layers.reserve(10);
	}

	LayerStack::~LayerStack()
	{
		Clear();
	}

	void LayerStack::OnUpdateAllLayers()
	{
		for (auto layer : m_layers)
		{
			layer->OnUpdate();
		}
	}

	void LayerStack::OnImGuiRenderAllLayers()
	{
		for (auto layer : m_layers)
		{
			layer->OnImGuiRender();
		}
	}

	void LayerStack::Clear()
	{
		for (auto layer : m_layers)
		{
			CEDAR_DELETE(layer);
		}

		m_layers.clear();
	}

} // namespace cedar
