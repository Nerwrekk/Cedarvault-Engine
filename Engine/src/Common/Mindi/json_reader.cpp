#include "Common/Mindi/json_reader.h"
#include "Common/Mindi/json_node.h"
#include "Common/Utils.h"

#include <iostream>
#include <fstream>

namespace Mindi
{
	bool json_reader::read(const std::string& file_name, json_node* out_node)
	{
		std::ifstream file(file_name, std::ios::in);
		if (!file.is_open())
			return false;

		out_node->type = json_type::Object;

		std::string line {};
		std::string token {};
		bool in_quotes {};
		bool is_first_curly {};
		json_values json;
		json.out_node = out_node;
		while (!file.eof())
		{
			std::getline(file, line);

			//skipping first curly brace
			if (line.find_first_of('{') != std::string::npos && !is_first_curly)
			{
				is_first_curly = true;
				const auto first_curly_iterator = std::find(line.begin(), line.end(), '{');
				const size_t char_index = std::distance(line.begin(), first_curly_iterator);

				if (line.length() - char_index == 0)
				{
					continue;
				}

				line = line.substr(char_index + 1, line.length());
			}

			//skip line if its empty
			if (line.find_first_not_of(' ') == std::string::npos)
			{
				continue;
			}

			for (const char& ch : line)
			{
				//string value
				if (ch == '\"')
				{
					in_quotes = !in_quotes;
					token.append(1, ch);
					continue;
				}

				//string value
				if (in_quotes)
				{
					token.append(1, ch);
					continue;
				}

				//property incoming
				if (ch == ':')
				{
					json.prop = token;
					clean_json_prop(json.prop);
					token.clear();
					continue;
				}

				//node array incoming
				if (ch == '[')
				{
					create_json_node(json, json_type::Array);
					token.clear();
					continue;
				}

				//node object incoming
				if (ch == '{')
				{
					create_json_node(json, json_type::Object);
					token.clear();
					continue;
				}

				if (ch != ',' && ch != ']' && ch != '}')
				{
					token.append(1, ch);
					continue;
				}

				//Add value to node
				utils::string::trim(token);
				if (!token.empty())
				{
					const auto type = get_json_type(token);
					json.type = type;
					json.value = &token;
					clean_json_value(*json.value);
					process_json_type(file, json);
					token.clear();
				}

				//closing node array
				if (ch == ']')
				{
					if (!json.out_node->parent_node)
					{
						continue;
					}

					if (json.out_node->parent_node->get_type() == json_type::Array)
					{
						json.out_node->parent_node->add(*json.out_node);
						//we don't want to free the memory here since we are giving the responsibility to parent_node
						//delete json_arr;
					}

					if (json.out_node->parent_node)
					{
						json.out_node = json.out_node->parent_node;
					}
					continue;
				}

				//closing node object
				if (ch == '}')
				{
					if (!json.out_node->parent_node)
					{
						continue;
					}

					if (json.out_node->parent_node->get_type() == json_type::Array)
					{
						json.out_node->parent_node->add(*json.out_node);
						//we don't one to free the memory since we are giving the responsibility to parent_node
						//delete new_object_node;
					}

					//resets so the parent node is the out node again
					if (json.out_node->parent_node)
					{
						json.out_node = json.out_node->parent_node;
					}
				}
			}
		}

		file.close();
		return true;
	}

	void json_reader::clean_json_prop(std::string& prop)
	{
		//old way
		//prop.erase(std::remove(prop.begin(), prop.end(), '\"'), prop.end());

		auto tabIt = std::remove(prop.begin(), prop.end(), '\t');
		auto colonIt = std::remove(prop.begin(), prop.end(), '\"');
		prop.erase(tabIt, prop.end());
		prop.erase(colonIt, prop.end());
		//this only removes the first instance
		//std::ranges::remove(prop, '\"');

		//replaces one char with another
		/*std::ranges::replace(prop, '"', '\0');*/
		utils::string::trim(prop);
	}

	void json_reader::clean_json_value(std::string& value)
	{
		auto tabIt = std::remove(value.begin(), value.end(), '\t');
		auto colonIt = std::remove(value.begin(), value.end(), '\"');
		value.erase(tabIt, value.end());
		value.erase(colonIt, value.end());
	}

	json_type json_reader::get_json_type(const std::string& value)
	{
		//note! if you don't add anything inside the curly braces, it will look like the debugger is skipping the if statement but its not!
		if (value.find('[') != std::string::npos)
		{
			//value is a json array
			return json_type::Array;
		}

		if (value.find('{') != std::string::npos)
		{
			//value is a json object
			return json_type::Object;
		}

		if (value.find('\"') != std::string::npos)
		{
			//value is string
			return json_type::String;
		}

		if (value.find('n') != std::string::npos)
		{
			//value is null
			return json_type::Null;
		}

		if (value.find('t') != std::string::npos ||
		    value.find('f') != std::string::npos)
		{
			//value is bool
			return json_type::Boolean;
		}

		//value is a number, checking if float or int
		if (value.find('.') != std::string::npos)
		{
			//value is float
			return json_type::Float;
		}

		//value is int
		if (std::isdigit(value[0]))
		{
			return json_type::Int;
		}

		//we should not get here
		return json_type::Null;
	}

	std::pair<std::string, std::string> json_reader::get_prop_and_value(const std::string& line)
	{
		const auto vec = utils::string::split(line, ':');
		std::string prop = vec.at(0);
		std::string value = vec.at(1);

		clean_json_prop(prop);

		utils::string::trim(prop);
		utils::string::trim(value);

		return std::make_pair(prop, value);
	}

	void json_reader::process_json_type(std::ifstream& file, json_values& json_values)
	{
		switch (json_values.type)
		{
		case json_type::Int:
			process_int(file, json_values);
			break;

		case json_type::Float:
			process_float(file, json_values);
			break;

		case json_type::String:
			process_string(file, json_values);
			break;

		case json_type::Boolean:
			process_bool(file, json_values);
			break;

		case json_type::Null:
			process_null(file, json_values);
			break;

		case json_type::Object:
		case json_type::Array:
		case json_type::Whitespace:
		default:
			std::cout << "SOMETHING WENT WRONG WHEN PROCESSING VALUE TYPE";
			break;
		}
	}

	void json_reader::process_string(std::ifstream& file, json_values& json_values)
	{
		set_value(json_values, json_values.value->c_str());
	}

	void json_reader::create_json_node(json_values& json_values, json_type type)
	{
		auto* parent_node = json_values.out_node;
		json_node* json_arr;
		if (!parent_node || parent_node->get_type() != json_type::Array)
			json_arr = &(*parent_node)[json_values.prop];
		else
			json_arr = new json_node {};

		json_arr->type = type;
		json_arr->parent_node = parent_node;
		json_values.out_node = json_arr;
	}

	void json_reader::process_float(std::ifstream& file, const json_values& json_values)
	{
		clean_json_value(*json_values.value);

		//TODO: check if value is Exponent
		set_value(json_values, utils::to_num<double>(*json_values.value));
	}

	void json_reader::process_int(std::ifstream& file, const json_values& json_values)
	{
		clean_json_value(*json_values.value);

		set_value(json_values, std::stoi(*json_values.value));
	}

	void json_reader::process_bool(std::ifstream& file, const json_values& json_values)
	{
		clean_json_value(*json_values.value);
		const bool val = (*json_values.value)[0] == 't' ? true : false;
		set_value(json_values, val);
	}

	void json_reader::process_null(std::ifstream& file, const json_values& json_values)
	{
		set_value(json_values, nullptr);
	}
} // namespace Mindi