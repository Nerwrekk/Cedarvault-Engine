#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <variant>
#include <typeinfo>
#include <stdexcept>

namespace Mindi
{

	enum class json_type
	{
		Int,
		Float,
		String,
		Boolean,
		Array,
		Object,
		Whitespace,
		Null
	};

	class json_node;

	using json_object = json_node;
	using json_array = std::vector<json_node*>;

	class json_node
	{
	public:
		json_node& operator=(const json_node& other);
		bool operator==(const json_node& r_node) const;
		json_node& operator=(json_node&& other) noexcept;

		json_node& operator[](const std::string& name);
		json_node& operator[](const int index) const;

		json_node& operator=(std::vector<int>&& value);
		json_node& operator=(const double value);
		json_node& operator=(const int value);
		json_node& operator=(const bool value);
		json_node& operator=(const char* value);
		//json_node& operator=(const std::string& value);

		/* json_node& operator+=(const std::string& value);
    json_node& operator+=(const float value);*/

	private:
		friend class json_writer;
		friend class json_reader;

		std::variant<
		    std::string,
		    bool,
		    int,
		    double,
		    json_object*,
		    json_array*>
		    m_content;

		json_type type = json_type::Null;

		json_node* parent_node = nullptr;
		std::vector<std::pair<std::string, json_node*>> m_json_nodes;
		std::unordered_map<std::string, size_t> m_map_json_nodes;

		template <typename T>
		void append_to_array(T raw_value)
		{
			json_node* node = new json_node();
			node->parent_node = this;

			if constexpr (std::is_integral_v<T>)
			{
				if (std::is_same_v<T, int>)
					node->set_int(raw_value);
				else if (std::is_same_v<T, bool>)
					node->set_bool(raw_value);
			}
			else if constexpr (std::is_floating_point_v<T>)
			{
				node->set_float(raw_value);
			}

			try
			{
				auto& _ = std::get<json_array*>(m_content);
			}
			catch (std::bad_variant_access const&)
			{
				//array was uninitialized
				m_content = new json_array();
			}

			std::get<json_array*>(m_content)->push_back(node);
		}

		template <typename T>
		void append_nested_array(std::vector<T>&& arr)
		{
			const auto arr_type = *typeid(arr.at(0)).name();

			json_node nested_node(this);
			nested_node.type = json_type::Array;
			nested_node.m_content = new json_array();
			for (T& element : arr)
			{
				json_node node {};
				node = element;

				nested_node.get_array().push_back(&node);
			}

			std::get<json_array*>(m_content)->push_back(&nested_node);
		}

	public:
		json_node();
		json_node(json_node* parent_node);
		json_node(json_node* parent_node, json_type type);
		json_node(const json_node& other);
		~json_node();
		json_node(json_node&& other) noexcept;

		void set_string(const std::string& str);
		[[nodiscard]] std::string get_string() const;

		void set_float(const double num);
		[[nodiscard]] double get_float() const;

		void set_int(const int num);
		[[nodiscard]] int get_int() const;

		void set_bool(const bool value);
		[[nodiscard]] bool get_bool() const;

		[[nodiscard]] json_object& get_obj() const;

		//Creates an json array
		template <typename T>
		void set_array(std::vector<T>&& arr)
		{
			type = json_type::Array;

			// const auto arr_type = *typeid(arr.at(0)).name();

			json_array json_nodes;
			for (T& element : arr)
			{
				json_node node(this);
				node = element;

				json_nodes.push_back(&node);
			}

			m_content = new json_array(json_nodes);

			arr.clear();
		}

		void set_array(std::vector<const char*>&& arr);

		[[nodiscard]] json_array& get_array() const;

		//Creates or appends to an json array
		template <typename T>
		void add(const T value)
		{
			if (type == json_type::Null)
				type = json_type::Array;

			if (type != json_type::Array)
				throw std::invalid_argument("tried to add value to node that was not an array");

			this->append_to_array(value);
		}

		template <typename T>
		void add(std::vector<T>&& value)
		{
			if (type == json_type::Null)
				type = json_type::Array;

			if (type != json_type::Array)
				throw std::invalid_argument("tried to add value to node that was not an array");

			this->append_nested_array(std::move(value));
		}

		//Creates or appends to an json array
		void add(const char* value);
		void add(json_node& json_arr);

		[[nodiscard]] json_type get_type() const;
	};
} // namespace Mindi

// std::vector<std::string>& operator=(std::vector<std::string>& test, std::string t)
// {
//     return test.push(t);
// }
// };
