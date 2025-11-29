#pragma once

#include "ECS/ECS.h"

#include <string>

namespace Mean
{
	class MeanScript
	{
	public:
		static bool Init();
		static bool SetupNativeBindings();
		static void Shutdown();
		static void CallMethod(const std::string& assemblyPath, const std::string& className, const std::string& methodName);

		static void InitManagedScriptEngine(const std::string& scriptDllPath);
		static void LoadScriptAssembly(const std::string& scriptDllPath);
		static void AttachScriptToEntity(cedar::Entity entity, char* scriptName);
		static void RemoveScriptEntity(cedar::Entity entity);
		static void OnUpdateAllScripts(float deltaTime);

		// void* LoadMeanManagedFunctionPtr(const std::filesystem::path& InAssemblyPath, const CharType* InTypeName, const CharType* InMethodName) const
		// {
		// 	void* funcPtr = nullptr;
		// 	int status = LoadAssembly(InAssemblyPath.c_str(), InTypeName, InMethodName, UNMANAGEDCALLERSONLY_METHOD, nullptr, &funcPtr);
		// 	// CORAL_VERIFY(status == StatusCode::Success && funcPtr != nullptr);
		// 	return funcPtr;
		// }
	};
} // namespace Mean