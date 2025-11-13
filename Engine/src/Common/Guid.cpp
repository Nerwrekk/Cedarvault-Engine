#include "Common/Guid.h"

#include "Common/Utils.h"

#include <array>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>

#if defined(_WIN32)
	#include <objbase.h> // CoCreateGuid
	#pragma comment(lib, "ole32.lib")
#else
	#include <unistd.h>
	#ifdef __has_include
		#if __has_include(<uuid/uuid.h>)
			#include <uuid/uuid.h>
			#include "Guid.h"
		#endif
	#endif
#endif

namespace cedar
{
	Guid::Guid()
	{
	}

	Guid::Guid(uint64_t high, uint64_t low)
	    : m_high(high), m_low(low)
	{
	}

	bool Guid::operator==(const Guid& other) const
	{
		return m_high == other.m_high &&
		       m_low == other.m_low;
	}
	bool Guid::operator!=(const Guid& other) const
	{
		return !(*this == other);
	}

	std::string Guid::ToString()
	{
		std::ostringstream ss;
		ss << m_high << "-" << m_low;

		return ss.str();
	}

#if defined(_WIN32)
	static inline std::pair<uint64_t, uint64_t> WindowsGenerateGuid()
	{
		GUID sysGuid;
		CoCreateGuid(&sysGuid);

		uint64_t high = (static_cast<uint64_t>(sysGuid.Data1) << 32) |
		                (static_cast<uint64_t>(sysGuid.Data2) << 16) | sysGuid.Data3;

		uint64_t low;
		for (int i = 0; i < 8; ++i)
		{
			low |= static_cast<uint64_t>(sysGuid.Data4[i]) << (8 * (7 - i));
		}

		return std::make_pair(high, low);
	}
#else
	static inline std::pair<uint64_t, uint64_t> LinuxGenerateGuid()
	{
		uuid_t sysUuid;
		uuid_generate(sysUuid);

		uint32_t data1 = (sysUuid[0] << 24) | (sysUuid[1] << 16) | (sysUuid[2] << 8) | sysUuid[3];
		uint16_t data2 = (sysUuid[4] << 8) | sysUuid[5];
		uint16_t data3 = (sysUuid[6] << 8) | sysUuid[7];
		std::array<uint8_t, 8> data4;
		std::memcpy(data4.data(), sysUuid + 8, 8);

		Guid cedarGuid;
		cedarGuid.m_high = (static_cast<uint64_t>(data1) << 32) |
		                   (static_cast<uint64_t>(data2) << 16) | data3;

		for (int i = 0; i < 8; ++i)
		{
			cedarGuid.m_low |= static_cast<uint64_t>(data4[i]) << (8 * (7 - i));
		}
		return cedarGuid;
	}
#endif

	std::pair<uint64_t, uint64_t> GuidGenerator::GenerateGuid()
	{
#if defined(_WIN32)
		return WindowsGenerateGuid();
#else
		return LinuxGenerateGuid();
#endif
	}

	std::pair<uint64_t, uint64_t> GuidGenerator::GenerateGuidFromString(const std::string& guidString)
	{
		auto vec      = utils::string::split(guidString, '-');
		uint64_t high = utils::to_num<uint64_t>(vec[0]);
		uint64_t low  = utils::to_num<uint64_t>(vec[1]);

		return std::make_pair(high, low);
	}
} // namespace cedar
