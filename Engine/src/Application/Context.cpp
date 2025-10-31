// #include "application/Context.h"
// #include "application/Layer.h"
// #include "platform/cross/CrossWindow.h"
// namespace Mean
// {
// 	AppContext::AppContext()
// 	{
// 		eventDispatcher = std::make_unique<EventDispatcher>();
// 		window = std::make_unique<CrossWindow>(WindowConfiguration::WindowConfiguration(), eventDispatcher.get());
// 		layers.reserve(10);
// 	}

// 	AppContext::~AppContext()
// 	{
// 		for (auto& layer : layers)
// 		{
// 			MEAN_DELETE(layer);
// 		}
// 	}
// }