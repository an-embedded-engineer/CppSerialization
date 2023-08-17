#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "Endian.h"

#include <cstdint>
#include <array>
#include <cassert>

namespace cpp_lib
{
    namespace binary
    {
        /* テンプレートで指定された算術型 <=> バイナリ(バイト配列)変換器 */
        template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
        union BinaryConversion
        {
            T       data;               /* バイナリ変換前データ */
            byte_t  byte[sizeof(T)];    /* バイナリ変換後データ(バイト配列) */
        };

        /* 算術型 <=> バイナリ(バイト配列)変換クラス */
        class BinaryConverter
        {
        public:
            /* テンプレートで指定された算術型のデータを指定されたエンディアンでバイナリ(バイト配列)に変換 */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const cpp_lib::endian::EndianType in_current_endian, const cpp_lib::endian::EndianType in_target_endian, const T& in_data, std::array<byte_t, sizeof(T)>& out_bytes)
            {
                /* 現在のエンディアンとターゲットエンディアンが異なる場合 */
                if (in_current_endian != in_target_endian)
                {
                    /* テンプレートで指定された算術型のデータをバイナリ(バイト配列)に変換(スワップあり) */
                    BinaryConverter::Convert(in_data, out_bytes, true);
                }
                else
                {
                    /* テンプレートで指定された算術型のデータをバイナリ(バイト配列)に変換(スワップなし) */
                    BinaryConverter::Convert(in_data, out_bytes, false);
                }
            }

            /* バイナリ(バイト配列)を指定されたエンディアンでテンプレートで指定された算術型のデータに変換 */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const cpp_lib::endian::EndianType in_current_endian, const cpp_lib::endian::EndianType in_target_endian, const std::array<byte_t, sizeof(T)>& in_bytes, T& out_data)
            {
                /* 現在のエンディアンとターゲットエンディアンが異なる場合 */
                if (in_current_endian != in_target_endian)
                {
                    /* バイナリ(バイト配列)をテンプレートで指定された算術型のデータに変換(スワップあり) */
                    BinaryConverter::Convert(in_bytes, out_data, true);
                }
                else
                {
                    /* バイナリ(バイト配列)をテンプレートで指定された算術型のデータに変換(スワップなし) */
                    BinaryConverter::Convert(in_bytes, out_data, false);
                }
            }

        private:
            /* テンプレートで指定された算術型のデータをバイナリ(バイト配列)に変換(スワップ有無を指定) */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const T& in_data, std::array<byte_t, sizeof(T)>& out_bytes, bool swap = false)
            {
                /* テンプレートで指定された算術型 <=> バイナリ(バイト配列)変換器 */
                cpp_lib::binary::BinaryConversion<T> conv{};

                /* 算術型データセット */
                conv.data = in_data;

                /* データサイズ取得 */
                size_t size = out_bytes.size();

                /* スワップあり */
                if (swap == true)
                {
                    /* データサイズ分バイト配列を逆順にコピー */
                    for (size_t i = 0; i < size; i++)
                    {
                        size_t j = (size - 1) - i;

                        out_bytes[i] = conv.byte[j];
                    }
                }
                /* スワップなし */
                else
                {
                    /* データサイズ分バイト配列をコピー */
                    for (size_t i = 0; i < size; i++)
                    {
                        out_bytes[i] = conv.byte[i];
                    }
                }
            }

            /* バイナリ(バイト配列)をテンプレートで指定された算術型のデータに変換(スワップ有無を指定) */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const std::array<byte_t, sizeof(T)>& in_bytes, T& out_data, bool swap = false)
            {
                /* テンプレートで指定された算術型 <=> バイナリ(バイト配列)変換器 */
                cpp_lib::binary::BinaryConversion<T> conv{};

                /* データサイズ取得 */
                size_t size = in_bytes.size();

                /* スワップあり */
                if (swap == true)
                {
                    /* データサイズ分バイト配列を逆順にコピー */
                    for (size_t i = 0; i < size; i++)
                    {
                        size_t j = (size - 1) - i;

                        conv.byte[i] = in_bytes[j];
                    }
                }
                /* スワップなし */
                else
                {
                    /* データサイズ分バイト配列をコピー */
                    for (size_t i = 0; i < size; i++)
                    {
                        conv.byte[i] = in_bytes[i];
                    }
                }

                /* 算術型データに変換して出力 */
                out_data = conv.data;
            }
        };
    }
}
