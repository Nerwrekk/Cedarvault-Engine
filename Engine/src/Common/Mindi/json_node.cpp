#include "Common/Mindi/json_node.h"

#include <algorithm>
#include <locale>
#include <iostream>
#include <fstream>

namespace Mindi
{

	json_node::json_node()
	{
	}

	json_node::json_node(json_node* parent_node)
	    : json_node(parent_node, json_type::Null)
	{
	}

	json_node::json_node(json_node* parent_node, json_type type)
	{
		if (!parent_node && type == json_type::Null)
		{
			this->parent_node = nullptr;
		}
		else
		{
			this->parent_node = parent_node;
		}

		if (type != json_type::Null)
			this->type = type;
	}

	json_node::json_node(const json_node& other)
	{
		//it was the copy constructor that was wrong, thats why a gizillion errors showed up
		//and the reason for that was that we were trying to copy unique_ptr and that is not allowed!
		std::cout << "copied" << "\n";
		type = other.type;
		parent_node = other.parent_node;

		for (auto& t : other.m_json_nodes)
		{
			m_json_nodes.push_back(t);
		}
		m_map_json_nodes = std::unordered_map(other.m_map_json_nodes);
	}

	json_node::json_node(json_node&& other) noexcept
	{
		//note to self!!! if we need to move a list we need to iterate through the entire list and "move" each element!
		if (std::holds_alternative<json_array*>(other.m_content))
		{
			this->m_content = new json_array();

			auto& arr = std::get<json_array*>(other.m_content);
			for (auto& element : *arr)
			{
				std::get<json_array*>(this->m_content)->push_back(element);
			}
		}
		else
			m_content = other.m_content;

		type = other.type;
		parent_node = other.parent_node;
		m_json_nodes = other.m_json_nodes;
		m_map_json_nodes = other.m_map_json_nodes;
	}

	json_node::~json_node()
	{
		for (auto& [key, node] : m_json_nodes)
		{
			if (node->get_type() == json_type::Array)
			{
				for (json_node* arrNode : node->get_array())
				{
					if (arrNode)
					{
						delete arrNode;
						arrNode = nullptr;
					}
				}
			}

			if (node)
			{
				delete node;
				node = nullptr;
			}
		}
	}

	void json_node::set_string(const std::string& str)
	{
		//this checks if the type has been set before, otherwise, we know it is gonna be a string node
		type = json_type::String;

		//this is for resizing the vector for reason??
		m_content = std::string(str);
	}

	std::string json_node::get_string() const
	{
		return std::get<std::string>(m_content);
	}

	void json_node::set_float(const double num)
	{
		type = json_type::Float;
		m_content = num;
	}

	double json_node::get_float() const
	{
		return std::get<double>(m_content);
	}

	void json_node::set_int(const int num)
	{
		type = json_type::Int;
		m_content = num;
	}

	int json_node::get_int() const
	{
		return std::get<int>(m_content);
	}

	void json_node::set_bool(const bool value)
	{
		m_content = value;
		type = json_type::Boolean;
	}

	bool json_node::get_bool() const
	{
		return std::get<bool>(m_content);
	}

	json_object& json_node::get_obj() const
	{
		return *std::get<json_object*>(m_content);
	}

	void json_node::set_array(std::vector<const char*>&& arr)
	{
		json_array json_nodes;
		for (const auto element : arr)
		{
			json_node node(this);
			node.set_string(std::string(element));

			json_nodes.push_back(&node);
		}

		m_content = new json_array(json_nodes);

		arr.clear();
	}

	json_array& json_node::get_array() const
	{
		return *std::get<json_array*>(m_content);
	}

	void json_node::add(const char* value)
	{
		if (type == json_type::Null)
			type = json_type::Array;

		if (type != json_type::Array)
			throw std::invalid_argument("tried to add value to node that was not an array");

		const auto node = new json_node(this);
		node->set_string(std::string(value));

		try
		{
			auto& _ = std::get<json_array*>(m_content);
		}
		catch (std::bad_variant_access const)
		{
			//array was uninitialized
			m_content = new json_array();
		}

		std::get<json_array*>(m_content)->push_back(node);
	}

	void json_node::add(json_node& json_arr)
	{
		if (type == json_type::Null)
			type = json_type::Array;

		if (type != json_type::Array)
			throw std::invalid_argument("tried to add value to node that was not an array");

		try
		{
			auto& _ = std::get<json_array*>(m_content);
		}
		catch (std::bad_variant_access const&)
		{
			//array was uninitialized
			m_content = new json_array();
		}

		std::get<json_array*>(m_content)->push_back(&json_arr);
	}

	json_type json_node::get_type() const
	{
		return type;
	}

	json_node& json_node::operator[](const std::string& name)
	{
		//if we acces it again and its still none, then its a json object
		if (this->get_type() == json_type::Null)
		{
			type = json_type::Object;
		}

		//check if the this node's map already contains a node with this name
		if (auto t = m_map_json_nodes.find(name); t == m_map_json_nodes.end())
		{
			//does not exists, we create it and then return it
			//ways you can insert a pair
			//for map
			//m_map_json_nodes.emplace(name, m_json_nodes.size());
			m_map_json_nodes.insert(std::make_pair(name, m_json_nodes.size()));

			//for vector:
			//m_json_nodes.push_back(std::make_pair(name, json_node()));
			//m_json_nodes.push_back({ name, json_node() });
			if (this->get_type() == json_type::Object)
			{
				//IMPORTANT by not using pointers in the vector, whenever we created another json_node, we copied over the node to the vector,
				//and lost the parent_node connection with the current node
				m_json_nodes.emplace_back(name, new json_node(this));
			}

			//m_json_nodes[m_map_json_nodes[name]].second.type = json_type::Null;
		}

		//it exists so return the node
		//you can immediately dereference a unique ptr
		return *m_json_nodes[m_map_json_nodes[name]].second;
	}

	json_node& json_node::operator[](const int index) const
	{
		if (this->get_type() != json_type::Array)
		{
			throw std::exception("current node is not a json_array");
		}
		//std::get<<json_array>>(m_content)->push_back(json_node(this));

		//TODO: check if index range is out of bounds
		return *std::get<json_array*>(m_content)->at(index);
	}

	json_node& json_node::operator=(std::vector<int>&& value)
	{
		set_array(std::move(value));

		return *this;
	}

	//Note to self! function position matters in the file!!
	json_node& json_node::operator=(const json_node& other)
	{
		if (this == &other)
			return *this;

		throw std::exception("not implemented yet");
	}

	bool json_node::operator==(const json_node& r_node) const
	{
		return this == &r_node;
	}

	//next time make sure we are in the move assignment and not copy assignment!!
	json_node& json_node::operator=(json_node&& other) noexcept
	{
		if (this == &other)
			return *this;

		type = json_type::Object;

		/*  type = other.type;
    parent_node = other.parent_node;
    m_content = other.m_content;
    m_json_nodes = std::move(other.m_json_nodes);
    m_map_json_nodes = other.m_map_json_nodes;*/

		return *this;
	}

	json_node& json_node::operator=(const double value)
	{
		set_float(value);

		return *this;
	}

	json_node& json_node::operator=(const int value)
	{
		set_int(value);

		return *this;
	}

	json_node& json_node::operator=(const bool value)
	{
		set_bool(value);

		return *this;
	}

	json_node& json_node::operator=(const char* value)
	{
		if (!value)
		{
			type = json_type::Null;
		}
		else
		{
			const auto string = std::string(value);
			set_string(string);
		}

		return *this;
	}
} // namespace Mindi

//json_node& json_node::operator=(const std::string& value)
//{
//	set_string(value);
//    return *this;
//}

//json_node& json_node::operator+=(const std::string& value)
//{
//    set_string(value, m_content.size());
//    return *this;
//}
//
//json_node& json_node::operator+=(const float value)
//{
//    set_float(value, m_content.size());
//    return *this;
//}
