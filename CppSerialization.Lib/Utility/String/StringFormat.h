#pragma once
#include <string>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <memory>
#include <type_traits>

namespace util
{
    namespace string
    {
        namespace detail
        {
            /* 型コンセプト判定 */
            template<bool con>
            using concept_t = typename std::enable_if<con, std::nullptr_t>::type;

            /* 列挙型(enum/enum class)の基底型を取得 */
            template<typename T>
            using underlying_type_t = typename std::underlying_type<T>::type;

            /* 列挙型(enum/enum class)を基底型にキャスト */
            template<typename T, concept_t<std::is_enum<T>::value> = nullptr>
            constexpr underlying_type_t<T> underlying_cast(T e)
            {
                return static_cast<underlying_type_t<T>>(e);
            }

#if __cpp_if_constexpr
            /* C++ 17版 */
            /* std::string型をconst char*に変換、列挙型(enum/enum class)を基底型に変換し、それ以外はそのまま出力 */
            template<typename T>
            auto Convert(T&& value)
            {
                /* std::string型をconst char*に変換 */
                if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, std::string>)
                {
                    return std::forward<T>(value).c_str();
                }
                /* 列挙型(enum/enum class)を基底型に変換 */
                else if constexpr (std::is_enum_v<T>)
                {
                    return std::forward<underlying_type_t<T>>(underlying_cast(value));
                }
                /* std::string型、列挙型(enum/enum class)以外は、そのまま出力 */
                else
                {
                    return std::forward<T>(value);
                }
            }
#else
            /* C++ 11/14版 */
            /* std::string型をconst char*に変換 */
            template<typename T, concept_t<std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value> = nullptr>
            auto Convert(T&& value)
            {
                return std::forward<T>(value).c_str();
            }

            /* 列挙型(enum/enum class)を基底型に変換 */
            template<typename T, concept_t<std::is_enum<T>::value> = nullptr>
            auto Convert(T&& value)
            {
                return std::forward<underlying_type_t<T>>(underlying_cast(value));
            }

            /* std::string型、列挙型(enum/enum class)以外は、そのまま出力 */
            template<typename T, concept_t<!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value && !std::is_enum<T>::value> = nullptr>
            auto Convert(T&& value)
            {
                return std::forward<T>(value);
            }
#endif

            /* 文字列のフォーマッティング(内部処理) */
            template<typename ... Args>
            std::string FormatInternal(const std::string& format, Args&& ... args)
            {
                /* フォーマット後の文字数を算出 */
                int str_len = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args) ...);

                /* フォーマット失敗 */
                if (str_len < 0)
                {
                    throw std::runtime_error("String Formatting Error : " + format);
                }
                else
                {
                    /* Nothing to do */
                }

                /* バッファサイズを算出(文字列長 + null文字サイズ) */
                size_t buffer_size = str_len + sizeof(char);

                /* バッファサイズ分メモリ確保 */
                std::unique_ptr<char[]> buffer(new char[buffer_size]);

                /* 文字列のフォーマット */
                std::snprintf(buffer.get(), buffer_size, format.c_str(), args ...);

                /* 文字列をstd::string型に変換して出力 */
                return std::string(buffer.get(), buffer.get() + str_len);
            }
        }

        /* 文字列のフォーマッティング */
        template<typename ... Args>
        std::string Format(const std::string& format, Args&& ... args)
        {
            /* 各パラメータの型を変換して、文字列のフォーマッティング */
            return detail::FormatInternal(format, detail::Convert(std::forward<Args>(args)) ...);
        }
    }
}

/* Format String Macro Function */
#define STRING_FORMAT(...) util::string::Format(__VA_ARGS__)
