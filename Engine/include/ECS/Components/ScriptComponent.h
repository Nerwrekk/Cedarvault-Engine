#pragma once

#include "Common/Core.h"

#include <vector>
#include <string>

namespace cedar
{
	struct ScriptComponent
	{
		DECL_TYPE_NAME(ScriptComponent)

		std::vector<std::string> Scripts;
		bool HasRunOnStart = false;

		ScriptComponent(std::vector<std::string>&& scripts = {})
		{
			Scripts.reserve(10);
			for (auto& script : scripts)
			{
				Scripts.push_back(script);
			}
		}
	};

} // namespace cedar
