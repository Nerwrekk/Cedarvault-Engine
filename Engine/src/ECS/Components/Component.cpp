#include "ECS/Components/Component.h"

namespace cedar
{
	// Define static members.
	std::unordered_map<std::type_index, unsigned int> ComponentRegistry::s_typeToId;
	uint32_t ComponentRegistry::s_nextId = 0;

	/*
	You're running into a classic issue where your static variable inside GetId() 
	is being instantiated separately in both the engine DLL and the game. 
	Since each binary (DLL and EXE) has its own memory space, each instance of Component<T>::GetId() 
	is maintaining its own separate static counter, leading to mismatched IDs.
	*/
	uint32_t ComponentRegistry::GetId(std::type_index type)
	{
		auto it = s_typeToId.find(type);
		if (it == s_typeToId.end())
		{
			// Assign a new ID and store it.
			uint32_t id = s_nextId++;
			s_typeToId[type] = id;

			return id;
		}

		return it->second;
	}
} // namespace cedar
