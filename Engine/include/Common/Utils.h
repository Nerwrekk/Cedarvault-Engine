#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace utils
{
	[[nodiscard]] std::vector<std::string> split_string(const std::string& words, char delimiter);

	void trim_string(std::string& line);

	template <typename T>
	std::string to_string(T val)
	{
		std::ostringstream ss {};
		ss << val;

		return ss.str();
	}

	template <typename T>
	constexpr T to_num(const std::string& value)
	{
		T num {};
		std::stringstream ss { value };
		ss >> num;

		return num;
	}

}