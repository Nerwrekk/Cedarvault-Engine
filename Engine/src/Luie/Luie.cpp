#include "Luie/Luie.h"

#include <filesystem>
#include "Common/Logger.h"
#include "Common/Utils.h"

namespace fs = std::filesystem;

namespace cedar
{
	namespace Luie
	{
		ScriptEngine::ScriptEngine()
		    : lua()
		{
			lua.open_libraries(sol::lib::base);
		}

		ScriptEngine::~ScriptEngine()
		{
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
					if (fs::is_regular_file(dirEntry.status()))
					{
						// Print the file name
						const auto fileName = dirEntry.path().stem().string();
						CEDAR_WARN("File: {}", fileName);

						//TODO: load scripts here
						lua.script_file(dirEntry.path().string());
						scripts[fileName] = dirEntry.path().string();
					}
				}
			}
			catch (const std::exception& e)
			{
				CEDAR_FATAL("{}", e.what());
			}
		}

		void ScriptEngine::CallFunction(const std::string& funcName)
		{
		}

		void ScriptEngine::ReloadScript(const std::string& name)
		{
		}
	} // namespace Luie

} // namespace cedar
