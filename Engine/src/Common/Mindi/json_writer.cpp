#include "Common/Mindi/json_writer.h"
#include "Common/Utils.h"

#include <fstream>
#include <functional>
#include <algorithm>
#include <iomanip>

bool is_new_line = false;

namespace Mindi
{
	bool json_writer::write(
	    const json_node& root_node,
	    const std::string& file_name,
	    const size_t num_of_indent)
	{
		if (!file_name.find(".json"))
		{
			//not a json file
			return false; //TODO: add proper handling if file dont have .json extension
		}

		//another way of doing a lambda, we are using this lambda to able to make the nodes write themselves in
		const std::function<void(const json_node&, std::ofstream&)> write = [&](const json_node& base_root_node, std::ofstream& file)
		{
			size_t index {};
			for (const auto& [child_prop, child_node] : base_root_node.m_json_nodes)
			{
				//check if current child is an object
				if (child_node->get_type() == json_type::Object)
				{
					write_object(child_prop, child_node, file, num_of_indent);
				}
				else if (child_node->get_type() == json_type::Array)
				{
					write_array(child_prop, child_node, file, num_of_indent);
				}
				else
				{
					//is not an json object, can write directly

					//TODO: check if the current nodes content is an array or not

					//checking if current base_root_node is the last base_root_node
					std::string comma = get_comma_or_empty(index, base_root_node.m_json_nodes.size());
					auto value = process_node(child_node);
					file << set_indent(num_of_indent) << "\"" << child_prop << "\"" << ": " << value << comma << "\n";
				}

				index++;
			}
		};

		std::ofstream file(file_name, std::ofstream::out);
		if (file.is_open())
		{
			//write open bracket
			file << "{" << "\n";

			write(root_node, file);

			//write closing bracket
			file << "}";

			file.close();
			return true;
		}

		return false;
	}

	void json_writer::write_object(const std::string& prop, const json_node* node, std::ofstream& file, const size_t num_of_indent)
	{
		//here we initilize the json object
		file << set_indent(num_of_indent) << "\"" << prop << "\"" << ": " << "{" << "\n";

		//here we write down all the properties and check for nested json objects
		for (auto& [child_prop, child_node] : node->m_json_nodes)
		{
			if (child_node->get_type() == json_type::Object)
			{
				write_object(child_prop, child_node, file, num_of_indent + 1);
				continue;
			}

			if (child_node->get_type() == json_type::Array)
			{
				write_array(child_prop, child_node, file, num_of_indent + 1);
				continue;
			}

			std::string comma = get_comma_or_empty(node->m_map_json_nodes.at(child_prop), node->m_json_nodes.size());
			auto value = process_node(child_node);
			file << set_indent(num_of_indent + 1) << "\"" << child_prop << "\"" << ": " << value << comma << "\n";
		}

		//here we close up the json object and checks if it is the last entry or not
		const std::string comma_or_empty = get_comma_or_empty(node->parent_node->m_map_json_nodes[prop], node->parent_node->m_json_nodes.size());
		file << set_indent(num_of_indent) << "}" << comma_or_empty << "\n";
	}

	void json_writer::write_arr_object(const json_node* node, std::ofstream& file, const size_t num_of_indent)
	{
		//here we initialize the json object
		file << "{" << "\n";
		size_t index {};
		for (const auto& [child_prop, child_node] : node->m_json_nodes)
		{
			if (child_node->get_type() == json_type::Array)
			{
				write_array(child_prop, child_node, file, 0);
				index++;
				continue;
			}

			if (child_node->get_type() == json_type::Object)
			{
				write_object(child_prop, child_node, file, num_of_indent);
				index++;
				continue;
			}

			std::string comma = get_comma_or_empty(index, node->m_json_nodes.size());
			auto value = process_node(child_node);
			file << set_indent(num_of_indent) << "\"" << child_prop << "\"" << ": " << value << comma << "\n";

			index++;
		}

		//here we close up the json object and checks if it is the last entry or not;
		const auto& parent_arr = std::get<json_array*>(node->parent_node->m_content);

		//here we got an error that said: binary '==': json_node 'does not define this operator
		//this was because we removed the unique_ptr from json_array and then std::ranges had no way of comparing 2 json_nodes because
		//I had not overloaded the 'operator=='
		const auto child_index = std::find(parent_arr->begin(), parent_arr->end(), node);
		/*if (child_index != parent_arr->end())
	{*/
		const size_t node_index = child_index - parent_arr->begin();
		if (node_index == parent_arr->size() - 1)
			file << set_indent(num_of_indent) << "}";
		else
			file << set_indent(num_of_indent) << "}, ";
		//}
	}

	bool has_nested_array = false;
	void json_writer::write_array(const std::string& prop, const json_node* node, std::ofstream& file,
	    const size_t num_of_indent)
	{
		if (node->parent_node->get_type() != json_type::Array)
		{
			file << set_indent(num_of_indent) << "\"" << prop << "\"" << ": " << "[";
		}
		else if (is_new_line)
		{
			file << "\n"
			     << set_indent(num_of_indent + 1) << "[";
			is_new_line = false;
		}
		else
		{
			file << "[";
		}

		//get array
		const auto& json_arr = std::get<json_array*>(node->m_content);
		size_t index {};
		for (auto element : *json_arr)
		{
			if (element->get_type() == json_type::Array)
			{
				write_array("", element, file, num_of_indent);

				const auto child_index = std::find(json_arr->begin(), json_arr->end(), element);
				if (child_index != json_arr->end())
				{
					const size_t node_index = child_index - json_arr->begin();
					if (node_index != json_arr->size() - 1)
						file << ", ";
				}
				has_nested_array = true;
				continue;
			}

			if (element->get_type() == json_type::Object)
			{
				write_arr_object(element, file, num_of_indent + 1);
				is_new_line = true;
				continue;
			}

			std::string comma {};
			const auto child_index = std::find(json_arr->begin(), json_arr->end(), element);
			if (child_index != json_arr->end())
			{
				const size_t node_index = child_index - json_arr->begin();
				if (node_index != json_arr->size() - 1)
					comma = ", ";
			}
			auto value = process_node(element);
			file << value << comma;

			index++;
		}

		//here we close up the json object and checks if it is the last entry or not
		const std::string comma_or_empty = get_comma_or_empty(node->parent_node->m_map_json_nodes[prop], node->parent_node->m_json_nodes.size());
		if (node->parent_node->get_type() != json_type::Array)
		{
			if (has_nested_array)
			{
				file << "\n"
				     << set_indent(num_of_indent) << "]" << comma_or_empty << "\n";
				has_nested_array = false;
			}
			else
			{
				file << "]" << comma_or_empty << "\n";
			}
		}
		else
		{
			file << "]";
		}
	}

	std::string json_writer::get_comma_or_empty(const size_t index, const size_t num_of_nodes)
	{
		if (num_of_nodes <= 0)
			return "";

		const bool is_last = index == num_of_nodes - 1;
		return is_last ? "" : ",";
	}

	std::string json_writer::set_indent(const size_t num_of_indent)
	{
		std::string new_indent = "\t";
		for (size_t i = 1; i < num_of_indent; ++i)
		{
			new_indent += "\t";
		}

		return new_indent;
	}

	std::string json_writer::process_node(const json_node* node)
	{
		switch (node->get_type())
		{
		case json_type::Float:
			return process_float(node->get_float());

		case json_type::Int:
			return std::to_string(node->get_int());

		case json_type::String:
			return "\"" + node->get_string() + "\"";

		case json_type::Boolean:
			return process_boolean(node->get_bool());

		case json_type::Null:
			return "null";

		case json_type::Array:
		case json_type::Object:
		case json_type::Whitespace:
		default:
			return "ERROR FAILED TO PROCESS NODE TYPE";
		}
	}

	std::string json_writer::process_float(const double value)
	{
		//TODO: check if value is Exponent
		auto float_str = utils::to_string(value);

		return float_str;
	}

	std::string json_writer::process_boolean(const bool value)
	{
		return value == true ? "true" : "false";
	}

} // namespace Mindi