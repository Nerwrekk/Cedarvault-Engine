#include "Luie/Luie.h"
#include "Luie/LuaBehaviour.h"
#include "Common/Logger.h"
#include "Common/Utils.h"
#include "ECS/Components/Components.h"
#include "Luie/LuieBindings.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace cedar
{
	namespace Luie
	{
		ScriptEngine::ScriptEngine()
		    : m_lua()
		{
			m_lua.open_libraries(sol::lib::base);

			m_lua.new_usertype<LuaBehaviour>("LuaBehaviour",
			    "new", sol::constructors<LuaBehaviour()>(),
			    "OnStart", &LuaBehaviour::OnStart,
			    "OnUpdate", &LuaBehaviour::OnUpdate);
		}

		ScriptEngine::~ScriptEngine()
		{
		}

		void ScriptEngine::Initialize()
		{
			m_lua.new_usertype<Entity>("entity",
			    "GetID", &Entity::GetId);

			// Base script class that all scripts inherit from
			m_lua.script(R"(
				LuieScript = {}
				LuieScript.__index = LuieScript
		
				function LuieScript:new(entity)
					local obj = setmetatable({}, self)
					obj.entity = entity  -- Store entity id reference
					obj.dog = "bark"
					return obj
				end

				function LuieScript:SetEntityPosition(x, y)
					SetPosition(self.entity, x, y)
				end

				function LuieScript:GetEntityPosition()
    				return GetPosition(self.entity)
				end

				function LuieScript:SetEntityVelocity(x, y)
    				SetVelocity(self.entity, x, y)
				end

				function LuieScript:GetEntityVelocity()
    				return GetVelocity(self.entity)
				end
			)");

			SetLuieBindings(m_lua);
		}

		void ScriptEngine::LoadScripts(const std::string& path)
		{
			try
			{
				if (!fs::exists(path) && !fs::is_directory(path))
				{
					CEDAR_FATAL("Path: \"{}\" Does not exist", path);
				}

				CEDAR_INFO("Path: {} exists!", path);

				for (const auto& dirEntry : fs::directory_iterator(path))
				{
					sol::table scriptEnv = m_lua.create_table();
					bool anyValid = false;
					if (fs::is_regular_file(dirEntry.status()))
					{
						// Print the file name
						const auto fileName = dirEntry.path().stem().string();
						CEDAR_WARN("File: {}", fileName);

						m_lua.script_file(dirEntry.path().string());

						sol::optional<sol::table> table = m_lua[fileName];
						if (table != sol::nullopt)
						{
							m_scripts[fileName] = m_lua[fileName];
						}
					}
				}
			}
			catch (const std::exception& e)
			{
				CEDAR_FATAL("{}", e.what());
			}
		}

		void ScriptEngine::CallFunction(const std::string& scriptFileName, const std::string& funcName)
		{
			auto it = m_scripts.find(scriptFileName);
			if (it != m_scripts.end())
			{
				sol::table luaTable = it->second;
				sol::function func = luaTable[funcName];

				if (func.valid())
				{
					func();
				}
			}

			// for (auto& [filemame, scriptEnv] : m_scripts)
			// {
			// 	sol::function startfunc = scriptEnv["OnStart"];
			// 	sol::function Updatefunc = scriptEnv["OnUpdate"];

			// 	if (startfunc.valid())
			// 	{
			// 		startfunc();
			// 	}

			// 	if (Updatefunc.valid())
			// 	{
			// 		Updatefunc();
			// 	}
			// }
		}

		void ScriptEngine::ReloadScript(const std::string& name)
		{
		}

		std::list<sol::table>& ScriptEngine::GetEntityScriptInstances(int entityId)
		{
			return m_entityScripts[entityId];
		}

		void ScriptEngine::AttachScriptToEntity(int entityId, sol::table& scriptInstance)
		{
			m_entityScripts[entityId].push_back(scriptInstance);
		}
	}
	// namespace Luie

} // namespace cedar
