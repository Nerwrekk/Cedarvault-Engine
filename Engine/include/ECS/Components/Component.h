#pragma once

#include "Common/Core.h"
#include <cstdint>
#include <typeindex>
#include <unordered_map>

namespace cedar
{
	struct CEDAR_API ComponentRegistry
	{
		ComponentRegistry() = default;

	protected:
		static uint32_t GetId(std::type_index type);

	private:
		static std::unordered_map<std::type_index, uint32_t> s_typeToId;
		static uint32_t s_nextId;
	};

	//NOTE when exporting this class using CEDAR_API, all sorts of linker errors showed up!
	template <typename T>
	class Component : public ComponentRegistry
	{
	public:
		static uint32_t GetId()
		{
			return ComponentRegistry::GetId(std::type_index(typeid(T)));
		}
	};
} // namespace cedar
