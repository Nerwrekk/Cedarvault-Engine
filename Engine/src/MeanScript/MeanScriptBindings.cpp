#include "MeanScript/MeanScriptBindings.h"

#include "ECS/Components/Components.h"
#include "Scene/SceneManager.h"

namespace Mean
{
	void SetEntityPosition(cedar::Entity entity, float x, float y)
	{
		auto transform        = entity.GetComponent<cedar::TransformComponent>();
		transform->Position.x = x;
		transform->Position.y = y;
	}

	void* GetTransformComponent(cedar::Entity entity)
	{
		return static_cast<void*>(entity.GetComponent<cedar::TransformComponent>());
	}

	bool HasComponent(cedar::Entity entity, const char* typeName)
	{
		if (std::strcmp(typeName, constants::RigidBodyComponent) == 0)
		{
			auto scene = cedar::SceneManager::Get()->GetActiveScene();
			if (scene)
			{
				return scene->HasComponent<cedar::RigidBodyComponent>(entity);
			}
		}

		if (std::strcmp(typeName, constants::AnimationComponent) == 0)
		{
			auto scene = cedar::SceneManager::Get()->GetActiveScene();
			if (scene)
			{
				return scene->HasComponent<cedar::AnimationComponent>(entity);
			}
		}

		if (std::strcmp(typeName, constants::BoxColliderComponent) == 0)
		{
			auto scene = cedar::SceneManager::Get()->GetActiveScene();
			if (scene)
			{
				return scene->HasComponent<cedar::BoxColliderComponent>(entity);
			}
		}

		if (std::strcmp(typeName, constants::SpriteComponent) == 0)
		{
			auto scene = cedar::SceneManager::Get()->GetActiveScene();
			if (scene)
			{
				return scene->HasComponent<cedar::SpriteComponent>(entity);
			}
		}

		if (std::strcmp(typeName, constants::ScriptComponent) == 0)
		{
			auto scene = cedar::SceneManager::Get()->GetActiveScene();
			if (scene)
			{
				return scene->HasComponent<cedar::ScriptComponent>(entity);
			}
		}

		if (std::strcmp(typeName, constants::CameraFollowComponent) == 0)
		{
			auto scene = cedar::SceneManager::Get()->GetActiveScene();
			if (scene)
			{
				return scene->HasComponent<cedar::CameraFollowComponent>(entity);
			}
		}

		return false;
	}

	void* GetComponent(cedar::Entity entity, const char* typeName)
	{
		if (!HasComponent(entity, typeName))
		{
			return nullptr;
		}

		if (std::strcmp(typeName, constants::RigidBodyComponent) == 0)
		{
			return static_cast<void*>(entity.GetComponent<cedar::RigidBodyComponent>());
		}

		if (std::strcmp(typeName, constants::AnimationComponent) == 0)
		{
			return static_cast<void*>(entity.GetComponent<cedar::AnimationComponent>());
		}

		if (std::strcmp(typeName, constants::BoxColliderComponent) == 0)
		{
			return static_cast<void*>(entity.GetComponent<cedar::BoxColliderComponent>());
		}

		if (std::strcmp(typeName, constants::SpriteComponent) == 0)
		{
			return static_cast<void*>(entity.GetComponent<cedar::SpriteComponent>());
		}

		if (std::strcmp(typeName, constants::ScriptComponent) == 0)
		{
			return static_cast<void*>(entity.GetComponent<cedar::ScriptComponent>());
		}

		if (std::strcmp(typeName, constants::CameraFollowComponent) == 0)
		{
			return static_cast<void*>(entity.GetComponent<cedar::CameraFollowComponent>());
		}

		return nullptr;
	}

	void AddComponent(cedar::Entity entity, const char* typeName)
	{
		auto scene = cedar::SceneManager::Get()->GetActiveScene();
		if (!scene)
		{
			CEDAR_FATAL("No scene is active yet we are trying to add a component to an entity");
		}
		//Check if we have already added this component
		if (HasComponent(entity, typeName))
		{
			return;
		}
		std::string str(typeName);
		auto it = scene->GetEntityRegister()->ComponentFactories.find(str);
		if (it != scene->GetEntityRegister()->ComponentFactories.end())
		{
			it->second(entity);
		}

		//TODO: Trying to see if this solution works
		scene->GetEntityRegister()->AddEntityToSystem(entity);
	}

	void Log(const char* msg, cedar::LogLevel level)
	{
		switch (level)
		{
		case cedar::LogLevel::INFO:
			CEDAR_INFO(msg);
			break;
		case cedar::LogLevel::TRACE:
			CEDAR_TRACE(msg);
			break;
		case cedar::LogLevel::DEBUG:
			CEDAR_DEBUG(msg);
			break;
		case cedar::LogLevel::WARN:
			CEDAR_WARN(msg);
			break;
		case cedar::LogLevel::ERROR:
			CEDAR_ERROR(msg);
			break;
		default:
			CEDAR_FATAL("Trying to log with log level that does not exist: LOG LEVEL");
			break;
		}
	}
}
