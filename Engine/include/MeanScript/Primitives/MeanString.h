#pragma once

#include "Common/Core.h"

#include <string>
#include <cstring>
#include <cstdlib>

namespace Mean
{
	class CEDAR_API MeanString
	{
	public:
		MeanString()
		{
			m_data = new char[1];
			// m_data = (char*)std::malloc(sizeof(char));
			m_size     = 1;
			m_capacity = 1;
		}

		MeanString(const char* string)
		    : m_data(nullptr), m_size(0), m_capacity(0)
		{
			SetString(string);
		}

		MeanString(std::string& string)
		    : m_data(nullptr), m_size(0), m_capacity(0)
		{
			m_data = new char[string.length()];
			std::memcpy(m_data, string.c_str(), string.length());
			m_size     = string.length();
			m_capacity = string.length();
		}

		MeanString(const MeanString& meanString)
		{
			m_data = new char[meanString.m_size];
			std::memcpy(m_data, meanString.m_data, meanString.m_size);
			m_size     = meanString.m_size;
			m_capacity = meanString.m_capacity;
		}

		MeanString& operator=(const MeanString& meanString)
		{
			m_data = new char[meanString.m_size];
			std::memcpy(m_data, meanString.m_data, meanString.m_size);
			m_size     = meanString.m_size;
			m_capacity = meanString.m_capacity;

			return *this;
		}

		~MeanString()
		{
			if (m_data)
			{
				delete[] m_data;
				m_data = nullptr;
			}
			// m_data = nullptr;
		}

		void SetString(const char* string)
		{
			if (!string || string[0] == '\0')
			{
				Clear();
				return;
			}

			auto newSize = std::strlen(string);
			if (!m_data || newSize > m_capacity)
			{
				Reallocate(newSize + 1); //+1 for null terminator
			}

			std::memcpy(m_data, string, newSize);
			m_size = newSize;
		}

		const char* GetNativeString()
		{
			return m_data ? m_data : "";
		}

		std::string GetString()
		{
			return m_data ? std::string(m_data, m_size) : "";
		}

		uint64_t GetSize()
		{
			return m_size;
		}

		void Clear()
		{
			if (m_data)
			{
				m_data[0] = '\0';
			}

			m_size = 0;
		}

	private:
		void Reallocate(uint64_t newCapacity)
		{
			char* newBuffer = new char[newCapacity];
			// char* newBuffer = (char*)std::malloc(newCapacity);
			if (m_data && m_size > 0)
			{
				std::memcpy(newBuffer, m_data, newCapacity);

				delete[] m_data;
				// std::free(m_data);
			}

			m_data     = newBuffer;
			m_capacity = newCapacity;
		}

	private:
		uint64_t m_size;
		uint64_t m_capacity;
		char* m_data;
	};

	//Bindings for Csharp to hande MeanStrings
	using MeanString_GetString_fn = const char* (*)(MeanString*);
	using MeanString_SetString_fn = void (*)(MeanString*, const char*);
	using MeanString_GetSize_fn   = uint64_t (*)(MeanString*);

	extern "C"
	{
		const char* MeanString_GetString(MeanString* meanStr);
		void MeanString_SetString(MeanString* meanStr, const char* newString);
		uint64_t MeanString_GetSize(MeanString* meanStr);
	}
} // namespace Mean