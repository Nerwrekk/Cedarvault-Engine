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
			void CallFunction(const std::string& scriptFileName, const std::string& funcName);
			void ReloadScript(const std::string& name);

			sol::state& GetLuaState()
			{
				return m_lua;
			}

		private:
			sol::state m_lua;
			//filename <-> lua table
			std::unordered_map<std::string, sol::table> m_scripts;
		};
	} // namespace luie
} // namespace cedar
