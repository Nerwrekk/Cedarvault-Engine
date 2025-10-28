#pragma once

// imports & exports
#ifdef CEDAR_EXPORT
	#ifdef _MSC_VER
		#define CEDAR_API __declspec(dllexport)
	#else
		#define CEDAR_API __attribute__((visibility("default")))
	#endif
#else
	#ifdef _MSC_VER
		#define CEDAR_API __declspec(dllimport)
	#else
		#define CEDAR_API
	#endif
#endif

//This macro is required for types that needs a unique ID during runtime through TypeRegistry
#define DECL_TYPE_NAME(Type)                   \
	static constexpr const char* GetTypeName() \
	{                                          \
		return #Type;                          \
	}

#define GET_NAME_LITERAL(T) #T