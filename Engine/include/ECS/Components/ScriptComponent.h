#pragma once

#include <vector>
#include <string>

namespace cedar
{
	struct ScriptComponent
	{
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
