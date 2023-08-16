#pragma once
#include "CommonTypes.h"
#include "Archive.h"
#include "FloatIntConverter.h"
#include "TypeTraits.h"

#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace serialization
{
    class TextSerialization
    {
    public:
        using Node = boost::property_tree::ptree;

    public:
        static TextSerialization& GetInstance();

    private:
        TextSerialization() = default;
        ~TextSerialization() = default;

    public:
        TextSerialization(const TextSerialization&) = delete;
        TextSerialization(TextSerialization&&) = delete;
        TextSerialization& operator=(const TextSerialization&) = delete;
        TextSerialization& operator=(TextSerialization&&) = delete;

    public:
        template <typename T>
        void Serialize(const T& in_data, const string_t& name, serialization::Archive& out_archive)
        {
            Node root_node{};

            this->Serialize(in_data, name, root_node);

            this->WriteText(root_node, out_archive);
        }

        template <typename T>
        void Deserialize(const serialization::Archive& in_archive, const string_t& name, T& out_data)
        {
            Node root_node{};

            this->ReadText(in_archive, root_node);

            this->Deserialize(root_node, name, out_data);
        }

    private:
        /* Primitive Types - Integer */
        template<typename T, util::type_traits::concept_t<std::is_integral<T>::value> = nullptr>
        void Serialize(const T& in_data, Node& out_node)
        {
            out_node.put_value(in_data);
        }

        template<typename T, util::type_traits::concept_t<std::is_integral<T>::value> = nullptr>
        void Deserialize(const Node& in_node, T& out_data)
        {
            if (auto value = in_node.get_value_optional<T>())
            {
                out_data = value.get();
            }
            else
            {
                throw std::invalid_argument("value is nothing");
            }
        }


        /* Primitive Types - Floating Point */
        template<typename T, util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
        void Serialize(const T& in_data, Node& out_node)
        {
            string_t in_str{};

            this->ToHexString(in_data, in_str);

            out_node.put_value(in_str);
        }

        template<typename T, util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
        void Deserialize(const Node& in_node, T& out_data)
        {
            string_t out_str{};
            if (auto value = in_node.get_value_optional<string_t>())
            {
                out_str = value.get();

                this->FromHexString(out_str, out_data);
            }
            else
            {
                throw std::invalid_argument("value is nothing");
            }
        }

        /* Enum Types */
        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        void Serialize(const T& in_data, Node& out_node)
        {
            this->Serialize(util::type_traits::underlying_cast(in_data), out_node);
        }

        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        void Deserialize(const Node& in_node, T& out_data)
        {
            util::type_traits::underlying_type_t<T> data{};

            this->Deserialize(in_node, data);

            out_data = static_cast<T>(data);
        }

        /* Container Types - std::array */
        template <typename T, size_t N>
        void Serialize(const std::array<T, N>& in_data, const string_t& name, Node& out_node)
        {
            auto& child_node = out_node.add(name, "");

            for (const auto& item : in_data)
            {
                this->Serialize(item, "item", child_node);
            }
        }

        template <typename T, size_t N>
        void Deserialize(const Node& in_node, const string_t& name, std::array<T, N>& out_data)
        {
            auto& child_node = in_node.get_child(name);

            size_t i = 0;

            for (const auto& item_node_pair : child_node)
            {
                T item{};

                this->Deserialize(item_node_pair.second, item);

                out_data[i] = item;

                i++;
            }
        }


        /* Container Types - std::vector */
        template <typename T>
        void Serialize(const std::vector<T>& in_data, const string_t& name, Node& out_node)
        {
            auto& child_node = out_node.add(name, "");

            for (const auto& item : in_data)
            {
                this->Serialize(item, "item", child_node);
            }
        }

        template <typename T>
        void Deserialize(const Node& in_node, const string_t& name, std::vector<T>& out_data)
        {
            auto& child_node = in_node.get_child(name);

            out_data.clear();

            out_data.reserve(child_node.size());

            for (const auto& item_node_pair : child_node)
            {
                T item{};

                this->Deserialize(item_node_pair.second, item);

                out_data.push_back(item);
            }
        }


        /* Container Types - std::pair */
        template <typename T1, typename T2>
        void Serialize(const std::pair<T1, T2>& in_data, Node& out_node)
        {
            this->Serialize(in_data.first, "first", out_node);
            this->Serialize(in_data.second, "second", out_node);
        }

        template <typename T1, typename T2>
        void Deserialize(const Node& in_node, std::pair<T1, T2>& out_data)
        {
            T1 first{};

            this->Deserialize(in_node, "first", first);

            T2 second{};

            this->Deserialize(in_node, "second", second);

            out_data = std::make_pair<T1, T2>(first, second);
        }


        /* Container Types - std::map */
        template <typename TKey, typename TValue>
        void Serialize(const std::map<TKey, TValue>& in_data, const string_t& name, Node& out_node)
        {
            auto& child_node = out_node.add(name, "");

            for (const auto& item : in_data)
            {
                this->Serialize(item, "item", child_node);
            }
        }

        template <typename TKey, typename TValue>
        void Deserialize(const Node& in_node, const string_t& name, std::map<TKey, TValue>& out_data)
        {
            auto& child_node = in_node.get_child(name);

            for (const auto& item_node_pair : child_node)
            {
                TKey key{};

                this->Deserialize(item_node_pair.second, "first", key);

                TValue value{};

                this->Deserialize(item_node_pair.second, "second", value);

                out_data.emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(value));
            }
        }

        /* Tuple Types */
        template <typename TUPLE, size_t ...I>
        void SerializeTupleImple(Node& out_node, TUPLE&& t, std::index_sequence<I...>)
        {
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(this->Serialize(std::get<1>(std::get<I>(t)), std::get<0>(std::get<I>(t)), out_node)), 0)...
            };
        }

        template <typename TUPLE, size_t ...I>
        void DeserializeTupleImple(const Node& in_node, TUPLE&& t, std::index_sequence<I...>)
        {
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(this->Deserialize(in_node, std::get<0>(std::get<I>(t)), std::get<1>(std::get<I>(t)))), 0)...
            };
        }

        template <typename TUPLE>
        void SerializeTuple(Node& out_node, TUPLE&& t)
        {
            this->SerializeTupleImple(out_node, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }

        template <typename TUPLE>
        void DeserializeTuple(const Node& in_node, TUPLE&& t)
        {
            this->DeserializeTupleImple(in_node, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }


        /* Class / Struct Types */
        template <class T>
        void Serialize(const T& in_data, Node& out_node, typename std::enable_if<std::is_class<T>::value>::type* = nullptr);

        template <class T>
        void Deserialize(const Node& in_node, T& out_data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr);


        /* Named Object */
        template <typename T>
        void Serialize(const T& in_data, const string_t& name, Node& out_node)
        {
            auto& child_node = out_node.add(name, "");

            this->Serialize(in_data, child_node);
        }

        template <typename T>
        void Serialize(const T& in_data, const char*& name, Node& out_node)
        {
            auto& child_node = out_node.add(name, "");

            this->Serialize(in_data, child_node);
        }

        template <typename T>
        void Deserialize(const Node& in_node, const string_t& name, T& out_data)
        {
            auto& child_node = in_node.get_child(name);

            this->Deserialize(child_node, out_data);
        }

        template <typename T>
        void Deserialize(const Node& in_node, const char*& name, T& out_data)
        {
            auto& child_node = in_node.get_child(name);

            this->Deserialize(child_node, out_data);
        }

    private:
        /* Primitive Types - Boolean */
        void Serialize(const bool_t& in_data, Node& out_node);
        void Deserialize(const Node& in_node, bool_t& out_data);

        /* Primitive Types - String */
        void Serialize(const string_t& in_data, Node& out_node);
        void Deserialize(const Node& in_node, string_t& out_data);

        /* Common */
        void WriteText(const Node& in_root_node, serialization::Archive& out_archive);
        void ReadText(const serialization::Archive& in_archive, Node& out_root_node);

        void ToHexString(const float32_t& in_data, string_t& out_data);
        void ToHexString(const float64_t& in_data, string_t& out_data);

        void FromHexString(const string_t& in_data, float32_t& out_data);
        void FromHexString(const string_t& in_data, float64_t& out_data);
    };
}
