#pragma once
#include "EndianType.h"
#include "FloatIntConverter.h"

#include <type_traits>

namespace cpp_lib
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

        /* 現在の実行環境のエンディアン判定 */
        inline cpp_lib::endian::EndianType GetEnvironmentEndian()
        {
            /* リトルエンディアン判定 */
            if (IsLittleEndian() == true)
            {
                return cpp_lib::endian::EndianType::Little;
            }
            else
            {
                return cpp_lib::endian::EndianType::Big;
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
                    /* バイト列をスワップ */
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
                    /* バイト列をスワップ */
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
                    uint32_t tmp_value = SwapBytes<uint32_t, sizeof(uint32_t)>()(cpp_lib::binary::FloatIntConverter<float, uint32_t>::ConvertToInt(value));

                    /* スワップしたバイト列をfloat型に再度変換 */
                    return cpp_lib::binary::FloatIntConverter<float, uint32_t>::ConvertToFloat(tmp_value);
                }
            };

            /* バイト列スワップ(倍精度浮動小数点) */
            template <>
            struct SwapBytes<double, 8>
            {
                inline double operator()(double value)
                {
                    /* uint64型に変換してバイト列をスワップ */
                    uint64_t tmp_value = SwapBytes<uint64_t, sizeof(uint64_t)>()(cpp_lib::binary::FloatIntConverter<double, uint64_t>::ConvertToInt(value));

                    /* スワップしたバイト列をdouble型に再度変換 */
                    return cpp_lib::binary::FloatIntConverter<double, uint64_t>::ConvertToFloat(tmp_value);
                }
            };

            /* バイト列スワップ(エンディアンが異なる場合) */
            template<cpp_lib::endian::EndianType From, cpp_lib::endian::EndianType To, class T>
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
            struct Swap<cpp_lib::endian::EndianType::Little, cpp_lib::endian::EndianType::Little, T>
            {
                inline T operator()(T value)
                {
                    /* そのまま返す */
                    return value;
                }
            };

            /* バイト列スワップ(ビッグエンディアン同士) */
            template <class T>
            struct Swap<cpp_lib::endian::EndianType::Big, cpp_lib::endian::EndianType::Big, T>
            {
                inline T operator()(T value)
                {
                    /* そのまま返す */
                    return value;
                }
            };
        }

        /* バイトスワップ */
        template<cpp_lib::endian::EndianType From, cpp_lib::endian::EndianType To, class T>
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
            if (GetEnvironmentEndian() == cpp_lib::endian::EndianType::Little)
            {
                /* エンディアン変換(リトル -> ビッグ) */
                return detail::Swap<cpp_lib::endian::EndianType::Little, cpp_lib::endian::EndianType::Big, T>()(value);
            }
            else
            {
                /* エンディアン変換(ビッグ -> リトル) */
                return detail::Swap<cpp_lib::endian::EndianType::Big, cpp_lib::endian::EndianType::Little, T>()(value);
            }
        }

        /* エンディアン変換 */
        template<class T, cpp_lib::endian::EndianType To>
        inline T ConvertEndian(T value)
        {
            /* 入力データサイズチェック */
            static_assert((sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8), "(sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8)");

            /* 入力データ型チェック */
            static_assert((std::is_arithmetic<T>::value), "(std::is_arithmetic<T>::value)");

            /* 現在の環境のエンディアンと指定されたエンディアンが異なる */
            if (GetEnvironmentEndian() != To)
            {
                /* 現在の環境のエンディアンがリトルエンディアン */
                if (GetEnvironmentEndian() == cpp_lib::endian::EndianType::Little)
                {
                    /* エンディアン変換(リトル -> ビッグ) */
                    return detail::Swap<cpp_lib::endian::EndianType::Little, cpp_lib::endian::EndianType::Big, T>()(value);
                }
                /* 現在の環境のエンディアンがビッグエンディアン */
                else
                {
                    /* エンディアン変換(ビッグ -> リトル) */
                    return detail::Swap<cpp_lib::endian::EndianType::Big, cpp_lib::endian::EndianType::Little, T>()(value);
                }
            }
            /* 現在の環境のエンディアンと指定されたエンディアンが同じ */
            else
            {
                /* エンディアン変換不要 */
                return value;
            }
        }
    }
}
