#include "TextSerialization.h"
#include "TextSerialization.hpp"
#include "DataTypeTraits.h"

#include <iomanip>

namespace serialization
{
    TextSerialization& TextSerialization::GetInstance()
    {
        static TextSerialization instance;
        return instance;
    }

    /* Class / Struct Types */
    template<class T>
    void TextSerialization::Serialize(const T& in_data, Node& out_node, typename std::enable_if<std::is_class<T>::value>::type*)
    {
        auto tuple = dm::DataTypeTraits<T>::GetNamedMembersAsTuple(in_data);

        this->SerializeTuple(out_node, tuple);
    }

    template<class T>
    void TextSerialization::Deserialize(const Node& in_node, T& out_data, typename std::enable_if<std::is_class<T>::value>::type*)
    {
        auto tuple = dm::DataTypeTraits<T>::GetNamedMembersAsTuple(out_data);

        this->DeserializeTuple(in_node, tuple);
    }


    /* Primitive Types - Boolean */
    void TextSerialization::Serialize(const bool_t& in_data, Node& out_node)
    {
        out_node.put_value(in_data);
    }

    void TextSerialization::Deserialize(const Node& in_node, bool_t& out_data)
    {
        if (auto value = in_node.get_value_optional<bool_t>())
        {
            out_data = value.get();
        }
        else
        {
            throw std::invalid_argument("value is nothing");
        }
    }

    /* Primitive Types - String */
    void TextSerialization::Serialize(const string_t& in_data, Node& out_node)
    {
        out_node.put_value(in_data);
    }

    void TextSerialization::Deserialize(const Node& in_node, string_t& out_data)
    {
        if (auto value = in_node.get_value_optional<string_t>())
        {
            out_data = value.get();
        }
        else
        {
            throw std::invalid_argument("value is nothing");
        }
    }

    /* Common */
    void TextSerialization::WriteText(const Node& in_root_node, serialization::Archive& out_archive)
    {
        std::stringstream ss;

        const int indent = 4;

        auto setting = boost::property_tree::xml_parser::xml_writer_make_settings<string_t>(' ', indent, boost::property_tree::xml_parser::widen<string_t>("utf-8"));

        boost::property_tree::write_xml(ss, in_root_node, setting);

        string_t in_str = ss.str();

        size_t text_len = in_str.length();

        size_t buffer_size = text_len + 1;

        out_archive.Reserve(buffer_size);

        size_t offset = 0;

        out_archive.Write(in_str, offset);
    }

    void TextSerialization::ReadText(const serialization::Archive& in_archive, Node& out_root_node)
    {
        std::stringstream ss;

        ss << in_archive.GetDataPtr();

        boost::property_tree::read_xml(ss, out_root_node);
    }

    void TextSerialization::ToHexString(const float32_t& in_data, string_t& out_data)
    {
        std::stringstream ss;

        util::binary::FloatIntConverter<float32_t, uint32_t> converter;

        uint32_t int_data = converter.ConvertToInt(in_data);

        ss << std::showbase;
        ss << std::setw(4);
        ss << std::hex << int_data;

        out_data = ss.str();
    }

    void TextSerialization::ToHexString(const float64_t& in_data, string_t& out_data)
    {
        std::stringstream ss;

        util::binary::FloatIntConverter<float64_t, uint64_t> converter;

        uint64_t int_data = converter.ConvertToInt(in_data);

        ss << std::showbase;
        ss << std::setw(8);
        ss << std::hex << int_data;

        out_data = ss.str();
    }

    void TextSerialization::FromHexString(const string_t& in_data, float32_t& out_data)
    {
        uint32_t int_data = std::stoul(in_data, nullptr, 16);

        util::binary::FloatIntConverter<float32_t, uint32_t> converter;

        out_data = converter.ConvertToFloat(int_data);
    }

    void TextSerialization::FromHexString(const string_t& in_data, float64_t& out_data)
    {
        uint64_t int_data = std::stoull(in_data, nullptr, 16);

        util::binary::FloatIntConverter<float64_t, uint64_t> converter;

        out_data = converter.ConvertToFloat(int_data);
    }
}
