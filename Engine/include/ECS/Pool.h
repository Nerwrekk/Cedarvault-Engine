#pragma once

#include <vector>
#include <cstdint>

namespace cedar
{
	class IPool
	{
	public:
		virtual ~IPool() = default;
	};

	template <typename T>
	class Pool : public IPool
	{
	public:
		Pool(int size = 100)
		{
			m_data.reserve(size);
		}

		virtual ~Pool() = default;

		bool IsEmpty()
		{
			return m_data.empty();
		};

		size_t Size()
		{
			return m_data.size();
		}

		void Resize(int size)
		{
			m_data.resize(size);
		};

		void Clear()
		{
			m_data.clear();
		};
		void Add(T* object)
		{
			m_data.push_back(object);
		};

		void Set(int index, T object)
		{
			m_data[index] = object;
		};

		T& Get(int index)
		{
			return static_cast<T&>(m_data.at(index));
		};

		T& operator[](uint32_t index)
		{
			return m_data[index];
		};

	private:
		//index == entity id
		std::vector<T> m_data;
	};
} // namespace cedar
