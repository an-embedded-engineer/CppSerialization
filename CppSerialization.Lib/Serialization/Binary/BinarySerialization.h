#pragma once
#include "CommonTypes.h"
#include "EndianType.h"
#include "Archive.h"
#include "BinaryConverter.h"
#include "TypeTraits.h"

namespace serialization
{
    class BinarySerialization
    {
    public:
        static BinarySerialization& GetInstance();

    private:
        BinarySerialization();
        ~BinarySerialization() = default;

    public:
        BinarySerialization(const BinarySerialization&) = delete;
        BinarySerialization(BinarySerialization&&) = delete;
        BinarySerialization& operator=(const BinarySerialization&) = delete;
        BinarySerialization& operator=(BinarySerialization&&) = delete;

    public:
        template <typename T>
        void CalculateSize(const T& in_data, size_t& out_size)
        {
            this->Calculate(in_data, out_size);
        }

        template <typename T>
        void Serialize(const T& in_data, serialization::Archive& out_archive)
        {
            size_t size = 0;

            this->CalculateSize(in_data, size);

            out_archive.Reserve(size);

            size_t offset = 0;

            this->Serialize(in_data, offset, out_archive);
        }

        template <typename T>
        void Deserialize(const serialization::Archive& in_archive, T& out_data)
        {
            size_t offset = 0;

            this->Deserialize(in_archive, offset, out_data);
        }

    private:
        /* Primitive Types - Integer */
        template<typename T, util::type_traits::concept_t<util::type_traits::is_nonbool_integral<T>::value> = nullptr>
        void Calculate(const T& in_data, size_t& out_size)
        {
            out_size += sizeof(in_data);
        }

        template<typename T, util::type_traits::concept_t<util::type_traits::is_nonbool_integral<T>::value> = nullptr>
        void Serialize(const T& in_data, size_t& offset, Archive& out_archive)
        {
            std::array<byte_t, sizeof(T)> in_bytes{};

            util::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, in_data, in_bytes);

            out_archive.Write(in_bytes, offset);
        }

        template<typename T, util::type_traits::concept_t<util::type_traits::is_nonbool_integral<T>::value> = nullptr>
        void Deserialize(const Archive& in_archive, size_t& offset, T& out_data)
        {
            std::array<byte_t, sizeof(T)> out_bytes{};

            in_archive.Read(out_bytes, offset);

            util::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, out_bytes, out_data);
        }

        /* Primitive Types - Floating Point */
        template<typename T, util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
        void Calculate(const T& in_data, size_t& out_size)
        {
            out_size += sizeof(in_data);
        }

        template<typename T, util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
        void Serialize(const T& in_data, size_t& offset, Archive& out_archive)
        {
            std::array<byte_t, sizeof(T)> in_bytes{};

            util::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, in_data, in_bytes);

            out_archive.Write(in_bytes, offset);
        }

        template<typename T, util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
        void Deserialize(const Archive& in_archive, size_t& offset, T& out_data)
        {
            std::array<byte_t, sizeof(T)> out_bytes{};

            in_archive.Read(out_bytes, offset);

            util::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, out_bytes, out_data);
        }

        /* Enum Types */
        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        void Calculate(const T& in_data, size_t& out_size)
        {
            this->Calculate(util::type_traits::underlying_cast(in_data), out_size);
        }

        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        void Serialize(const T& in_data, size_t& offset, Archive& out_archive)
        {
            this->Serialize(util::type_traits::underlying_cast(in_data), offset, out_archive);
        }

        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        void Deserialize(const Archive& in_archive, size_t& offset, T& out_data)
        {
            util::type_traits::underlying_type_t<T> data{};

            this->Deserialize(in_archive, offset, data);

            out_data = static_cast<T>(data);
        }


        /* Container Type - std::array */
        template <typename T, size_t N>
        void Calculate(const std::array<T, N>& in_data, size_t& out_size)
        {
            out_size += sizeof(size_t);

            for (const auto& item : in_data)
            {
                this->Calculate(item, out_size);
            }
        }

        template <typename T, size_t N>
        void Serialize(const std::array<T, N>& in_data, size_t& offset, Archive& out_archive)
        {
            this->Serialize(in_data.size(), offset, out_archive);

            for (const auto& item : in_data)
            {
                this->Serialize(item, offset, out_archive);
            }
        }

        template <typename T, size_t N>
        void Deserialize(const Archive& in_archive, size_t& offset, std::array<T, N>& out_data)
        {
            size_t size = 0;

            this->Deserialize(in_archive, offset, size);

            for (size_t i = 0; i < size; i++)
            {
                T item{};

                this->Deserialize(in_archive, offset, item);

                out_data[i] = item;
            }
        }


        /* Container Type - std::vector */
        template <typename T>
        void Calculate(const std::vector<T>& in_data, size_t& out_size)
        {
            out_size += sizeof(size_t);

            for (const auto& item : in_data)
            {
                this->Calculate(item, out_size);
            }
        }

        template <typename T>
        void Serialize(const std::vector<T>& in_data, size_t& offset, Archive& out_archive)
        {
            this->Serialize(in_data.size(), offset, out_archive);

            for (const auto& item : in_data)
            {
                this->Serialize(item, offset, out_archive);
            }
        }

        template <typename T>
        void Deserialize(const Archive& in_archive, size_t& offset, std::vector<T>& out_data)
        {
            size_t size = 0;

            this->Deserialize(in_archive, offset, size);

            out_data.reserve(size);

            for (size_t i = 0; i < size; i++)
            {
                T item{};

                this->Deserialize(in_archive, offset, item);

                out_data.push_back(item);
            }
        }


        /* Container Type - std::pair */
        template <typename T1, typename T2>
        void Calculate(const std::pair<T1, T2>& in_data, size_t& out_size)
        {
            this->Calculate(in_data.first, out_size);
            this->Calculate(in_data.second, out_size);
        }

        template <typename T1, typename T2>
        void Serialize(const std::pair<T1, T2>& in_data, size_t& offset, Archive& out_archive)
        {
            this->Serialize(in_data.first, offset, out_archive);
            this->Serialize(in_data.second, offset, out_archive);
        }

        template <typename T1, typename T2>
        void Deserialize(const Archive& in_archive, size_t& offset, std::pair<T1, T2>& out_data)
        {
            T1 first{};

            this->Deserialize(in_archive, offset, first);

            T2 second{};

            this->Deserialize(in_archive, offset, second);
        }


        /* Container Type - std::map */
        template <typename TKey, typename TValue>
        void Calculate(const std::map<TKey, TValue>& in_data, size_t& out_size)
        {
            out_size += sizeof(size_t);

            for (const auto& item : in_data)
            {
                this->Calculate(item, out_size);
            }
        }

        template <typename TKey, typename TValue>
        void Serialize(const std::map<TKey, TValue>& in_data, size_t& offset, Archive& out_archive)
        {
            this->Serialize(in_data.size(), offset, out_archive);

            for (const auto& item : in_data)
            {
                this->Serialize(item, offset, out_archive);
            }
        }

        template <typename TKey, typename TValue>
        void Deserialize(const Archive& in_archive, size_t& offset, std::map<TKey, TValue>& out_data)
        {
            size_t size = 0;

            this->Deserialize(in_archive, offset, size);

            for (size_t i = 0; i < size; i++)
            {
                TKey key{};

                this->Deserialize(in_archive, offset, key);

                TValue value{};

                this->Deserialize(in_archive, offset, value);

                out_data.emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(value));
            }
        }


        /* Tuple Types */
        template <typename TUPLE, size_t ...I>
        void CalculateTupleImple(size_t& out_size, TUPLE&& t, std::index_sequence<I...>)
        {
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(this->Calculate(std::get<I>(t), out_size)), 0)...
            };
        }

        template <typename TUPLE, size_t ...I>
        void SerializeTupleImple(size_t& offset, Archive& out_archive, TUPLE&& t, std::index_sequence<I...>)
        {
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(this->Serialize(std::get<I>(t), offset, out_archive)), 0)...
            };
        }

        template <typename TUPLE, size_t ...I>
        void DeserializeTupleImple(const Archive& in_archive, size_t& offset, TUPLE&& t, std::index_sequence<I...>)
        {
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(this->Deserialize(in_archive, offset, std::get<I>(t))), 0)...
            };
        }


        template <typename TUPLE>
        void CalculateTuple(size_t& out_size, TUPLE&& t)
        {
            this->CalculateTupleImple(out_size, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }

        template <typename TUPLE>
        void SerializeTuple(size_t& offset, Archive& out_archive, TUPLE&& t)
        {
            this->SerializeTupleImple(offset, out_archive, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }

        template <typename TUPLE>
        void DeserializeTuple(const Archive& in_archive, size_t& offset, TUPLE&& t)
        {
            this->DeserializeTupleImple(in_archive, offset, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }

        /* Class / Struct Types */
        template <class T>
        void Calculate(const T& in_data, size_t& out_size, typename std::enable_if<std::is_class<T>::value>::type* = nullptr);

        template <class T>
        void Serialize(const T& in_data, size_t& offset, Archive& out_archive, typename std::enable_if<std::is_class<T>::value>::type* = nullptr);

        template <class T>
        void Deserialize(const Archive& in_archive, size_t& offset, T& out_data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr);

    private:
        /* Primitive Types - Boolean */
        void Calculate(const bool_t& in_data, size_t& out_size);
        void Serialize(const bool_t& in_data, size_t& offset, Archive& out_archive);
        void Deserialize(const Archive& in_archive, size_t& offset, bool_t& out_data);

        /* Primitive Types - String */
        void Calculate(const string_t& in_data, size_t& out_size);
        void Serialize(const string_t& in_data, size_t& offset, Archive& out_archive);
        void Deserialize(const Archive& in_archive, size_t& offset, string_t& out_data);

    private:
        util::endian::EndianType m_CurrentEndian;
        util::endian::EndianType m_TargetEndian;
    };
}
