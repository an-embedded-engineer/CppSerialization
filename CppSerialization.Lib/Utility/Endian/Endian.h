#pragma once
#include "EndianType.h"
#include "FloatIntConverter.h"

#include <type_traits>

namespace util
{
    namespace endian
    {
        /* リトルエンディアン判定 */
        inline bool IsLittleEndian()
        {
            /* 0ビット目が先頭に来ているかどうかを判定 : 先頭に来ていたらリトルエンディアン */
            int data = 1;
            bool result = *reinterpret_cast<char*>(&data) == 1;
            return result;
        }

        /* ビッグエンディアン判定 */
        inline bool IsBigEndian()
        {
            /* リトルエンディアンでなければビッグエンディアン */
            return !IsLittleEndian();
        }

        /* 実行環境エンディアン判定 */
        inline util::endian::EndianType GetEnvironmentEndian()
        {
            /* リトルエンディアン判定 */
            if (IsLittleEndian() == true)
            {
                return util::endian::EndianType::Little;
            }
            else
            {
                return util::endian::EndianType::Big;
            }
        }

        namespace detail
        {
            /* バイト列スワップ(デフォルト) */
            template <typename T, size_t size>
            struct SwapBytes;

            /* バイト列スワップ(1byte) */
            template <typename T>
            struct SwapBytes<T, 1>
            {
                inline T operator()(T value)
                {
                    /* そのまま返す */
                    return value;
                }
            };

            /* バイト列スワップ(2byte) */
            template <typename T>
            struct SwapBytes<T, 2>
            {
                inline T operator()(T value)
                {
                    /* バイト列をスワップ */
                    return ((((value) & 0xFF00) >> 8)
                            | (((value) & 0x00FF) << 8));
                }
            };

            /* バイト列スワップ(4byte) */
            template <typename T>
            struct SwapBytes<T, 4>
            {
                inline T operator()(T value)
                {
                    return ((((value) & 0xFF000000) >> 24)
                            | (((value) & 0x00FF0000) >> 8)
                            | (((value) & 0x0000FF00) << 8)
                            | (((value) & 0x000000FF) << 24));
                }
            };

            /* バイト列スワップ(8byte) */
            template <typename T>
            struct SwapBytes<T, 8>
            {
                inline T operator()(T value)
                {
                    return ((((value) & 0xFF00000000000000ull) >> 56)
                            | (((value) & 0x00FF000000000000ull) >> 40)
                            | (((value) & 0x0000FF0000000000ull) >> 24)
                            | (((value) & 0x000000FF00000000ull) >> 8)
                            | (((value) & 0x00000000FF000000ull) << 8)
                            | (((value) & 0x0000000000FF0000ull) << 24)
                            | (((value) & 0x000000000000FF00ull) << 40)
                            | (((value) & 0x00000000000000FFull) << 56));
                }
            };

            /* バイト列スワップ(単精度浮動小数点) */
            template <>
            struct SwapBytes<float, 4>
            {
                inline float operator()(float value)
                {
                    /* uint32型に変換してバイト列をスワップ */
                    uint32_t tmp_value = SwapBytes<uint32_t, sizeof(uint32_t)>()(util::binary::FloatIntConverter<float, uint32_t>::ConvertToInt(value));
                    /* スワップしたバイト列をfloat型に再度変換 */
                    return util::binary::FloatIntConverter<float, uint32_t>::ConvertToFloat(tmp_value);
                }
            };

            /* バイト列スワップ(倍精度浮動小数点) */
            template <>
            struct SwapBytes<double, 8>
            {
                inline double operator()(double value)
                {
                    /* uint64型に変換してバイト列をスワップ */
                    uint64_t tmp_value = SwapBytes<uint64_t, sizeof(uint64_t)>()(util::binary::FloatIntConverter<double, uint64_t>::ConvertToInt(value));
                    /* スワップしたバイト列をdouble型に再度変換 */
                    return util::binary::FloatIntConverter<double, uint64_t>::ConvertToFloat(tmp_value);
                }
            };

            /* バイト列スワップ(エンディアンが異なる場合) */
            template<util::endian::EndianType From, util::endian::EndianType To, class T>
            struct Swap
            {
                inline T operator()(T value)
                {
                    /* バイト列をスワップ */
                    return SwapBytes<T, sizeof(T)>()(value);
                }
            };

            /* バイト列スワップ(リトルエンディアン同士) */
            template <class T>
            struct Swap<util::endian::EndianType::Little, util::endian::EndianType::Little, T>
            {
                inline T operator()(T value)
                {
                    /* そのまま返す */
                    return value;
                }
            };

            /* バイト列スワップ(ビッグエンディアン同士) */
            template <class T>
            struct Swap<util::endian::EndianType::Big, util::endian::EndianType::Big, T>
            {
                inline T operator()(T value)
                {
                    /* そのまま返す */
                    return value;
                }
            };
        }

        /* バイトスワップ */
        template<util::endian::EndianType From, util::endian::EndianType To, class T>
        inline T ByteSwap(T value)
        {
            /* 入力データサイズチェック */
            static_assert((sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8), "(sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8)");

            /* 入力データ型チェック */
            static_assert((std::is_arithmetic<T>::value), "(std::is_arithmetic<T>::value)");

            /* エンディアン変換 */
            return detail::Swap<From, To, T>()(value);
        }

        /* エンディアン変換 */
        template<class T>
        inline T ConvertEndian(T value)
        {
            /* 入力データサイズチェック */
            static_assert((sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8), "(sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8)");

            /* 入力データ型チェック */
            static_assert((std::is_arithmetic<T>::value), "(std::is_arithmetic<T>::value)");

            /* リトルエンディアン */
            if (GetEnvironmentEndian() == util::endian::EndianType::Little)
            {
                /* エンディアン変換(リトル -> ビッグ) */
                return detail::Swap<util::endian::EndianType::Little, util::endian::EndianType::Big, T>()(value);
            }
            else
            {
                /* エンディアン変換(ビッグ -> リトル) */
                return detail::Swap<util::endian::EndianType::Big, util::endian::EndianType::Little, T>()(value);
            }
        }
    }
}
