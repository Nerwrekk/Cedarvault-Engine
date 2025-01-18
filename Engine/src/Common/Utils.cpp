#include "Common/Utils.h"
#include <sstream>

std::vector<std::string> utils::split_string(const std::string& words, const char delimiter)
{
	std::vector<std::string> all_words {};
	std::string current_word {};

	std::stringstream string_stream(words);

	while (!string_stream.eof())
	{
		std::getline(string_stream, current_word, delimiter);
		all_words.push_back(current_word);
	}

	return all_words;
}

void utils::trim_string(std::string& line)
{
	line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
	line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

	////trim beginning
	//const auto value_size = line.find_first_not_of(' ');
	//line.replace(0, value_size, "");

	////trim end
	//const auto end_index = line.find_last_not_of(' ');
	//const auto end_whitespace = line.find_last_of(' ');
	//line.replace(end_index + 1, end_whitespace, "");
}