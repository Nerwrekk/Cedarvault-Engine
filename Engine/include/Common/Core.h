#pragma once

// imports & exports
#ifdef CEDAR_STATIC
	#define CEDAR_API
#else
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
#endif

#define UNREFERENCED_PARAMETER(P) (void)(P)

//This macro is required for types that needs a unique ID during runtime through TypeRegistry
#define DECL_TYPE_NAME(Type)                   \
	static constexpr const char* GetTypeName() \
	{                                          \
		return #Type;                          \
	}

#define GET_NAME_LITERAL(T) #T

// free memory
// Ensure safe memory management
#define CEDAR_DELETE(ptr)  \
	do                     \
	{                      \
		auto* tmp = (ptr); \
		delete tmp;        \
		(ptr) = nullptr;   \
	} while (0)

#define CEDAR_DELETE_ARRAY(ptr) \
	do                          \
	{                           \
		auto* tmp = (ptr);      \
		delete[] tmp;           \
		(ptr) = nullptr;        \
	} while (0)
