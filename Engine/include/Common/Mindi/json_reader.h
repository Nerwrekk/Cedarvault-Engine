#pragma once
#include <string>

#include "json_node.h"

struct json_values
{
	json_values() {};
	json_values(json_type type, const std::string& prop, std::string& value, json_node* out_node)
	{
		this->type = type;
		this->prop = prop;
		this->value = &value;
		this->out_node = out_node;
	}

	json_type type {};
	std::string prop;
	std::string* value;
	json_node* out_node;
};

class json_reader
{
public:
	static bool read(const std::string& file_name, json_node* out_node);

private:
	static void clean_json_prop(std::string& prop);
	static void clean_json_value(std::string& value);

	[[nodiscard]] static json_type get_json_type(const std::string& value);

	static void create_json_node(json_values& json_values, json_type type);
	static std::pair<std::string, std::string> get_prop_and_value(const std::string& line);

	static void process_json_type(std::ifstream& file, json_values& json_values);
	static void process_string(std::ifstream& file, json_values& json_values);
	static void process_float(std::ifstream& file, const json_values& json_values);
	static void process_int(std::ifstream& file, const json_values& json_values);
	static void process_bool(std::ifstream& file, const json_values& json_values);
	static void process_null(std::ifstream& file, const json_values& json_values);

	template <typename T>
	static void set_value(const json_values& json_values, T value)
	{
		if (json_values.out_node->type == json_type::Array)
			json_values.out_node->add(value);
		else
			(*json_values.out_node)[json_values.prop] = value;
	}
};
