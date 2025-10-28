#pragma once

#include "Common/Core.h"

#include <string>
#include <cstdint>

// Engine core provides this function (must be defined in a single .cpp compiled into the core)
CEDAR_API uint32_t register_type_name(const char* typeName);

template <typename T>
uint32_t TypeIdOf()
{
	// static inside template ensures one call per type per process; the assigned id is the one from the core registry
	static uint32_t id = register_type_name(T::GetTypeName());
	return id;
}
