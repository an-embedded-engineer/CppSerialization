#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "DataTypeTraits.h"
#include "RandomGenerator.h"

/* 乱数データ生成時のコンテナ最大/最小サイズ */
#define MIN_CONTAINER_SIZE  (1)     /* 最小コンテナサイズ */
#define MAX_CONTAINER_SIZE  (30)    /* 最大コンテナサイズ */

namespace cpp_lib
{
    namespace random
    {
        /* 乱数データ生成クラス */
        class RandomDataGenerator
        {
        public:
            /* std::array型乱数データ生成 */
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

            /* std::vector型乱数データ生成 */
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

            /* std::pair型乱数データ生成 */
            template <typename T1, typename T2>
            static void Generate(std::pair<T1, T2>& data)
            {
                T1 first{};
                T2 second{};

                RandomDataGenerator::Generate(first);
                RandomDataGenerator::Generate(second);

                data = { first, second };
            }

            /* std::map型乱数データ生成 */
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

            /* 列挙体(enum/enum class)型乱数データ生成 */
            template<typename T>
            static void Generate(T& data, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr)
            {
                /* EnumDataTypeTraitsからenumの最大/最小値を取得し基底型にキャスト */
                cpp_lib::type_traits::underlying_type_t<T> min_value = cpp_lib::type_traits::underlying_cast<T>(cpp_lib::type_traits::EnumDataTypeTraits<T>::GetMinValue());
                cpp_lib::type_traits::underlying_type_t<T> max_value = cpp_lib::type_traits::underlying_cast<T>(cpp_lib::type_traits::EnumDataTypeTraits<T>::GetMaxValue());

                /* 基底型で乱数生成 */
                cpp_lib::type_traits::underlying_type_t<T> underlying_data = GET_RANDOM_INT(min_value, max_value);

                /* 元のenum/enum class型にキャストしてセット */
                data = static_cast<T>(underlying_data);
            }


            /* クラス/構造体(class/struct)型メンバ乱数データ生成 */
            template <typename TUPLE, size_t ...I>
            static void GenerateTupleImple(TUPLE&& t, std::index_sequence<I...>)
            {
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(RandomDataGenerator::Generate(std::get<I>(t))), 0)...
                };
            }

            /* クラス/構造体(class/struct)型メンバ乱数データ生成 */
            template <typename TUPLE>
            static void GenerateTuple(TUPLE&& t)
            {
                RandomDataGenerator::GenerateTupleImple(std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* クラス/構造体(class/struct)型メンバ乱数データ生成 */
            template<typename T>
            static void Generate(T& data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* メンバのタプル取得 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(data);

                /* メンバのタプルから乱数データ生成 */
                RandomDataGenerator::GenerateTuple(tuple);
            }

        public:
            /* 論理型(bool)乱数データ生成 */
            static void Generate(bool& data);

            /* 8bit符号付整数型(int8)乱数データ生成 */
            static void Generate(int8_t& data);

            /* 16bit符号付整数型(int16)乱数データ生成 */
            static void Generate(int16_t& data);

            /* 32bit符号付整数型(int32)乱数データ生成 */
            static void Generate(int32_t& data);

            /* 64bit符号付整数型(int64)乱数データ生成 */
            static void Generate(int64_t& data);

            /* 8bit符号無整数型(uint8)乱数データ生成 */
            static void Generate(uint8_t& data);

            /* 16bit符号無整数型(uint16)乱数データ生成 */
            static void Generate(uint16_t& data);

            /* 32bit符号無整数型(uint32)乱数データ生成 */
            static void Generate(uint32_t& data);

            /* 64bit符号無整数型(uint64)乱数データ生成 */
            static void Generate(uint64_t& data);

            /* 32bit浮動小数型(float)乱数データ生成 */
            static void Generate(float32_t& data);

            /* 32bit浮動小数型(double)乱数データ生成 */
            static void Generate(float64_t& data);

            /* 文字列型(string)乱数データ生成 */
            static void Generate(std::string& data);
        };
    }
}
