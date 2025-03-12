#pragma once

#include "ECS/Components/Components.h"
#include "Common/Logger.h"
#include "Common/Input.h"
#include "Common/Time.h"
#include "Luie/Luie.h"

namespace cedar
{

	class ScriptSystem : public BaseSystem
	{
	public:
		ScriptSystem(Luie::ScriptEngine* scriptEngine)
		{
			p_luieEngine = scriptEngine;
			RequireComponent<ScriptComponent>();
		}

		virtual void Update() override
		{
			for (auto& entity : GetSystemEntities())
			{
				auto scriptComp = entity.GetComponent<ScriptComponent>();
				//OnStart
				if (!scriptComp->HasRunOnStart)
				{
					scriptComp->HasRunOnStart = true;
					for (sol::table& scriptInstance : p_luieEngine->GetEntityScriptInstances(entity.GetId()))
					{
						sol::function onStartFunc = scriptInstance["OnStart"];
						if (onStartFunc.valid())
						{
							onStartFunc(scriptInstance);
						}
					}
				}

				//OnUpdate
				for (sol::table& scriptInstance : p_luieEngine->GetEntityScriptInstances(entity.GetId()))
				{
					sol::function onUpdateFunc = scriptInstance["OnUpdate"];
					if (onUpdateFunc.valid())
					{
						onUpdateFunc(scriptInstance, Time::DeltaTime);
					}
				}
			}
		}

		virtual void AddEntityToSystem(Entity entity) override
		{
			m_entities.push_back(entity);

			auto scriptComp = entity.GetComponent<ScriptComponent>();

			for (auto& script : scriptComp->Scripts)
			{
				auto& lua = p_luieEngine->GetLuaState();
				sol::table scriptClass = lua[script];
				sol::function constructor = scriptClass["new"];

				if (!constructor.valid())
				{
					CEDAR_FATAL("Error: Script {} does not have a valid 'new' function!", script);
				}

				sol::table scriptInstance = constructor(scriptClass, sol::make_object(lua, entity));

				//TODO: keep the line below for now, but we prob don't need it
				// lua[script + entity.GetId()] = scriptInstance;
				p_luieEngine->AttachScriptToEntity(entity.GetId(), scriptInstance);
			}
		}

	private:
		Luie::ScriptEngine* p_luieEngine;
	};
} // namespace cedar
