#pragma once

#include <cstdint>
#include <utility>
#include <string>

namespace cedar
{
	class GuidGenerator;

	class Guid
	{
	public:
		Guid();
		Guid(uint64_t high, uint64_t low);

		inline uint64_t GetHighData();
		inline uint64_t GetLowData();

		bool operator==(const Guid& other) const;

		std::string ToString();

	private:
		friend class GuidGenerator;
		uint64_t m_high;
		uint64_t m_low;
	};

	class GuidGenerator
	{
	public:
		static std::pair<uint64_t, uint64_t> GenerateGuid();
		static std::pair<uint64_t, uint64_t> GenerateGuidFromString(const std::string& guidString);

	private:
#if defined(_WIN32)
		static inline std::pair<uint64_t, uint64_t> WindowsGenerateGuid();
#else
		static inline std::pair<uint64_t, uint64_t> LinuxGenerateGuid();
#endif
	};
} // namespace cedar
