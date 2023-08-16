#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "RandomGenerator.h"

#define MIN_CONTAINER_SIZE  (1)     /* Min Container Size */
#define MAX_CONTAINER_SIZE  (30)    /* Max Container Size */

namespace debug
{
    class RandomDataGenerator
    {
    public:
        /* std::array^f[^ถฌ */
        template <typename T, size_t N>
        static void Generate(std::array<T, N>& data)
        {
            size_t size = N;

            for (size_t i = 0; i < size; i++)
            {
                T item{};

                RandomDataGenerator::Generate(item);

                data[i] = item;
            }
        }

        /* std::vector^f[^ถฌ */
        template <typename T>
        static void Generate(std::vector<T>& data)
        {
            size_t size = GET_RANDOM_INT(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE);

            data.reserve(size);

            for (size_t i = 0; i < size; i++)
            {
                T item{};

                RandomDataGenerator::Generate(item);

                data.push_back(item);
            }
        }

        /* std::pair^f[^ถฌ */
        template <typename T1, typename T2>
        static void Generate(std::pair<T1, T2>& data)
        {
            T1 first{};
            T2 second{};

            RandomDataGenerator::Generate(first);
            RandomDataGenerator::Generate(second);

            data = { first, second };
        }

        /* std::map^f[^ถฌ */
        template <typename T1, typename T2>
        static void Generate(std::map<T1, T2>& data)
        {
            size_t size = GET_RANDOM_INT(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE);

            for (size_t i = 0; i < size; i++)
            {
                T1 key{};
                T2 value{};

                RandomDataGenerator::Generate(key);
                RandomDataGenerator::Generate(value);

                data[key] = value;
            }
        }

        /* ๑ฬ(enum/enum class)^f[^ถฌ */
        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        static void Generate(T& data);


        /* NX/\ขฬ(class/struct)^of[^ถฌ */
        template <typename TUPLE, size_t ...I>
        static void GenerateTupleImple(TUPLE&& t, std::index_sequence<I...>)
        {
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(RandomDataGenerator::Generate(std::get<I>(t))), 0)...
            };
        }

        /* NX/\ขฬ(class/struct)^of[^ถฌ */
        template <typename TUPLE>
        static void GenerateTuple(TUPLE&& t)
        {
            RandomDataGenerator::GenerateTupleImple(std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }

        /* NX/\ขฬ(class/struct)^f[^ถฌ */
        template<typename T, util::type_traits::concept_t<std::is_class<T>::value> = nullptr>
        static void Generate(T& data);

    public:
        /* _^(bool)f[^ถฌ */
        static void Generate(bool& data);

        /* 8bittฎ^(int8)f[^ถฌ */
        static void Generate(int8_t& data);

        /* 16bittฎ^(int16)f[^ถฌ */
        static void Generate(int16_t& data);

        /* 32bittฎ^(int32)f[^ถฌ */
        static void Generate(int32_t& data);

        /* 64bittฎ^(int64)f[^ถฌ */
        static void Generate(int64_t& data);

        /* 8bitณฎ^(uint8)f[^ถฌ */
        static void Generate(uint8_t& data);

        /* 16bitณฎ^(uint16)f[^ถฌ */
        static void Generate(uint16_t& data);

        /* 32bitณฎ^(uint32)f[^ถฌ */
        static void Generate(uint32_t& data);

        /* 64bitณฎ^(uint64)f[^ถฌ */
        static void Generate(uint64_t& data);

        /* 32bitฎฌ^(float)f[^ถฌ */
        static void Generate(float32_t& data);

        /* 32bitฎฌ^(double)f[^ถฌ */
        static void Generate(float64_t& data);

        /* ถ๑^(string)f[^ถฌ */
        static void Generate(std::string& data);
    };
}
