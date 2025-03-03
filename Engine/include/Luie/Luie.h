#pragma once

#include <sol/sol.hpp>
#include <unordered_map>
#include <string>

namespace cedar
{
	namespace Luie
	{
		class ScriptEngine
		{
		public:
			ScriptEngine();
			~ScriptEngine();

			void LoadScripts(const std::string& path);
			void CallFunction(const std::string& funcName);
			void ReloadScript(const std::string& name);

			sol::state& GetLuaState()
			{
				return lua;
			}

		private:
			sol::state lua;
			//filename <-> file path
			std::unordered_map<std::string, std::string> scripts;
		};
	} // namespace luie
} // namespace cedar
