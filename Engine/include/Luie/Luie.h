#pragma once

#include "ECS/ECS.h"

#include <sol/sol.hpp>
#include <unordered_map>
#include <list>
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

			void Initialize();

			void LoadScripts(const std::string& path);
			void CallFunction(const std::string& scriptFileName, const std::string& funcName);
			void ReloadScript(const std::string& name);

			void AttachScriptToEntity(int entityId, sol::table& scriptInstance);
			std::list<sol::table>& GetEntityScriptInstances(int entityId);

			sol::state& GetLuaState()
			{
				return m_lua;
			}

		private:
			sol::state m_lua;
			//filename <-> lua table
			std::unordered_map<std::string, sol::table> m_scripts;
			//entity id <-> scriptinstances tables
			std::unordered_map<int, std::list<sol::table>> m_entityScripts;
		};
	} // namespace luie
} // namespace cedar
