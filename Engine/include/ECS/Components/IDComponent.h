#pragma once

#include "Common/Guid.h"
#include "Common/Logger.h"

namespace cedar
{
	struct CEDAR_API IDComponent
	{
		DECL_TYPE_NAME(IDComponent);

		Guid guid;

		IDComponent()
		{
			auto [high, low] = GuidGenerator::GenerateGuid();
			guid             = Guid(high, low);

			CEDAR_INFO("IDComponent: {}", guid.ToString());
		}

		IDComponent(uint64_t high, uint64_t low)
		{
			guid = Guid(high, low);
		}
	};
} // namespace cedar
