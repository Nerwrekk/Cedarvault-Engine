#pragma once

#include "ECS/Components/Components.h"
#include "Common/Logger.h"
#include "Common/Input.h"
#include "Common/Time.h"
#include "MeanScript/MeanScript.h"

namespace cedar
{
	class MeanScriptSystem : public BaseSystem
	{
	public:
		MeanScriptSystem()
		{
			RequireComponent<ScriptComponent>();
		}

		virtual void Update() override
		{
			Mean::MeanScript::OnUpdateAllScripts(Time::DeltaTime);
		}

		virtual void AddEntityToSystem(Entity entity) override
		{
			if (std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end())
			{
				//has already been added
				return;
			}

			m_entities.push_back(entity);

			auto scriptComp = entity.GetComponent<ScriptComponent>();
			for (auto& script : scriptComp->Scripts)
			{
				Mean::MeanScript::AttachScriptToEntity(entity, (char*)script.c_str());
			}
		}
	};
} // namespace cedar