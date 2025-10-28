#pragma once

#include <filesystem>

#define CEDAR_EXPAND_MACRO(x) x
#define CEDAR_STRINGIFY_MACRO(x) #x

#ifdef CEDAR_ENABLE_ASSERTS
	#if defined(_WIN32)
		#define CEDAR_DEBUGBREAK() __debugbreak()
	#elif defined(linux)
		#include <signal.h>
		#define CEDAR_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
#else
	#define CEDAR_DEBUGBREAK()
#endif

#ifdef CEDAR_ENABLE_ASSERTS
    // static asserts
	#if defined(__clang__) || defined(__gcc__)
		#define CEDAR_STATIC_ASSERT _Static_assert
	#else
		#define CEDAR_STATIC_ASSERT static_assert
	#endif

    // Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
    // provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define CEDAR_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
		{                                                     \
			if ((check))                                      \
			{                                                 \
				CEDAR##type##ERROR(msg, __VA_ARGS__);         \
				CEDAR_DEBUGBREAK();                           \
			}                                                 \
		}
	#define CEDAR_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CEDAR_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define CEDAR_INTERNAL_ASSERT_NO_MSG(type, check) CEDAR_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CEDAR_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define CEDAR_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define CEDAR_INTERNAL_ASSERT_GET_MACRO(...) CEDAR_EXPAND_MACRO(CEDAR_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CEDAR_INTERNAL_ASSERT_WITH_MSG, CEDAR_INTERNAL_ASSERT_NO_MSG))

    // Currently accepts at least the condition and one additional parameter (the message) being optional
	#define CEDAR_ASSERT(...) CEDAR_EXPAND_MACRO(CEDAR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
	#define CEDAR_CORE_ASSERT(...) CEDAR_EXPAND_MACRO(CEDAR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#else
	#define CEDAR_ASSERT(...)
	#define CEDAR_CORE_ASSERT(...)
#endif
