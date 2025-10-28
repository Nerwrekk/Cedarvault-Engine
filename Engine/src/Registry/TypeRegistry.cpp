// TypeRegistry.cpp (in the core engine library; only one copy in the process)
#include "Registry/TypeRegistry.h"

#include <unordered_map>
#include <mutex>
#include <atomic>
#include <string>

static std::atomic<uint32_t> g_next { 1 };
static std::unordered_map<std::string, uint32_t> g_map;
static std::mutex g_mutex;

uint32_t register_type_name(const char* typeName)
{
	std::lock_guard<std::mutex> lk(g_mutex);

	auto it = g_map.find(typeName);
	if (it != g_map.end())
	{
		return it->second;
	}
	uint32_t id = g_next++;
	g_map.emplace(typeName, id);

	return id;
}
