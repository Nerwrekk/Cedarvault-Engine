#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace utils
{
	namespace string
	{
		[[nodiscard]] std::vector<std::string> split(const std::string& words, char delimiter);
		void trim(std::string& line);
		void replace(std::string& line, char replace_from, char replace_to);
		void replace(std::string& line, std::string& replace_from, std::string& replace_to);

	} // namespace string

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