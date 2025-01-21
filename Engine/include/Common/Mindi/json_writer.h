#pragma once
#include "json_node.h"

#include <string>

namespace Mindi
{
	class json_node;

	class json_writer
	{
	public:
		static bool write(const json_node& root_node, const std::string& file_name, const size_t num_of_indent = 1, const char list_sep = ',');

	private:
		static void write_object(const std::string& prop, const json_node* node, std::ofstream& file, const size_t num_of_indent);
		static void write_arr_object(const json_node* node, std::ofstream& file, const size_t num_of_indent);
		static void write_array(const std::string& prop, const json_node* node, std::ofstream& file, const size_t num_of_indent);

		static [[nodiscard]] std::string get_comma_or_empty(const size_t index, const size_t num_of_nodes);
		static [[nodiscard]] std::string set_indent(const size_t num_of_indent);

		static [[nodiscard]] std::string process_node(const json_node* node);
		static [[nodiscard]] std::string process_object(const json_node* node);
		static [[nodiscard]] std::string process_float(const double value);
		static [[nodiscard]] std::string process_boolean(const bool value);
	};

} // namespace Mindi