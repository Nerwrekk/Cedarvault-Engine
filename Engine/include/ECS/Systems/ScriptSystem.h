#pragma once

#include "ECS/Components/Components.h"
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
				for (auto& script : scriptComp->Scripts)
				{
					if (!scriptComp->HasRunOnStart)
					{
						scriptComp->HasRunOnStart = true;
						p_luieEngine->CallFunction(script, "OnStart");
					}

					p_luieEngine->CallFunction(script, "OnUpdate");
				}
			}
		}

	private:
		Luie::ScriptEngine* p_luieEngine;
	};
} // namespace cedar
