#pragma once

#include <string>

namespace Mean
{
	class MeanScript
	{
	public:
		static bool Init();
		static void Shutdown();
		static void CallMethod(const std::string& assemblyPath, const std::string& className, const std::string& methodName);
	};
} // namespace Mean