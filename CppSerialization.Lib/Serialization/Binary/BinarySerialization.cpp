#include "BinarySerialization.h"
#include "BinarySerialization.hpp"
#include "DataTypeTraits.h"
#include "Endian.h"

namespace serialization
{
    BinarySerialization& BinarySerialization::GetInstance()
    {
        static BinarySerialization instance;
        return instance;
    }

    BinarySerialization::BinarySerialization()
        : m_CurrentEndian(util::endian::GetEnvironmentEndian())
        , m_TargetEndian(util::endian::EndianType::Network)
    {
    }


    /* Class / Struct Types */
    template<class T>
    void BinarySerialization::Calculate(const T& in_data, size_t& out_size, typename std::enable_if<std::is_class<T>::value>::type*)
    {
        auto tuple = dm::DataTypeTraits<T>::GetMembersAsTuple(in_data);

        this->CalculateTuple(out_size, tuple);
    }

    template <class T>
    void BinarySerialization::Serialize(const T& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<T>::value>::type*)
    {
        auto tuple = dm::DataTypeTraits<T>::GetMembersAsTuple(in_data);

        this->SerializeTuple(offset, out_archive, tuple);
    }

    template <class T>
    void BinarySerialization::Deserialize(const Archive& in_archive, size_t& offset, T& out_data, typename std::enable_if<std::is_class<T>::value>::type*)
    {
        auto tuple = dm::DataTypeTraits<T>::GetMembersAsTuple(out_data);

        this->DeserializeTuple(in_archive, offset, tuple);
    }

    /* Primitive Types - Boolean */
    void BinarySerialization::Calculate(const bool_t& in_data, size_t& out_size)
    {
        out_size += sizeof(bool_t);
    }

    void BinarySerialization::Serialize(const bool_t& in_data, size_t& offset, Archive& out_archive)
    {
        byte_t in_byte = in_data == false ? 0 : 1;

        out_archive.Write(in_byte, offset);
    }

    void BinarySerialization::Deserialize(const Archive& in_archive, size_t& offset, bool_t& out_data)
    {
        byte_t out_byte = 0;

        in_archive.Read(out_byte, offset);

        out_data = (out_byte == 0) ? false : true;
    }

    /* Primitive Types - String */
    void BinarySerialization::Calculate(const string_t& in_data, size_t& out_size)
    {
        out_size += sizeof(size_t);
        out_size += in_data.size();
    }

    void BinarySerialization::Serialize(const string_t& in_data, size_t& offset, Archive& out_archive)
    {
        this->Serialize(in_data.size(), offset, out_archive);

        for (const auto& c : in_data)
        {
            byte_t in_byte = static_cast<byte_t>(c);

            out_archive.Write(in_byte, offset);
        }
    }

    void BinarySerialization::Deserialize(const Archive& in_archive, size_t& offset, string_t& out_data)
    {
        size_t size = 0;

        this->Deserialize(in_archive, offset, size);

        out_data.clear();

        out_data.reserve(size);

        for (size_t i = 0; i < size; i++)
        {
            byte_t out_byte = 0;

            in_archive.Read(out_byte, offset);

            out_data.push_back(static_cast<char>(out_byte));
        }
    }
}
