#pragma once

#include "ECS/Components/Components.h"
#include "Common/Logger.h"
#include "Common/Input.h"
#include "Common/CedarTime.h"
#include "MeanScript/MeanScript.h"

namespace cedar
{
	class MeanScriptSystem : public BaseSystem
	{
	public:
		DECL_TYPE_NAME(MeanScriptSystem);

		MeanScriptSystem()
		{
			RequireComponent<ScriptComponent>();
		}

		virtual void FixedUpdate(float fixedDeltaTime) override
		{
			Mean::MeanScript::OnUpdateAllScripts(fixedDeltaTime);
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

		virtual void RemoveEntityFromSystem(Entity entity) override
		{
			Mean::MeanScript::RemoveScriptEntity(entity);

			//Parent function
			BaseSystem::RemoveEntityFromSystem(entity);
		}
	};
} // namespace cedar