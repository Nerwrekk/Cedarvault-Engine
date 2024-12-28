#pragma once

#include <vector>
#include <cstdint>

namespace cedar
{
	class IPool
	{
	public:
		virtual ~IPool();
	};

	template <typename T>
	class Pool : IPool
	{
	public:
		Pool(int size = 100)
		{
			Resize(size);
		}

		virtual ~Pool() = default;

		bool IsEmpty()
		{
			return m_data.empty();
		};

		int Size()
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
		void Add(T object)
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
			return m_data.at(index);
		};

	private:
		std::vector<T> m_data;
	};
} // namespace cedar
