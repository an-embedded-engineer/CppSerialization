#pragma once
#include "TypeTraits.h"

#include <string>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <memory>

namespace cpp_lib
{
    namespace string
    {
        namespace detail
        {
#if __cpp_if_constexpr
            /* C++ 17�� */
            /* std::string�^��const char*�ɕϊ��A�񋓌^(enum/enum class)�����^�ɕϊ����A����ȊO�͂��̂܂܏o�� */
            template<typename T>
            auto Convert(T&& value)
            {
                /* std::string�^��const char*�ɕϊ� */
                if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, std::string>)
                {
                    return std::forward<T>(value).c_str();
                }
                /* �񋓌^(enum/enum class)�����^�ɕϊ� */
                else if constexpr (std::is_enum_v<T>)
                {
                    return std::forward<cpp_lib::type_traits::underlying_type_t<T>>(cpp_lib::type_traits::underlying_cast(value));
                }
                /* std::string�^�A�񋓌^(enum/enum class)�ȊO�́A���̂܂܏o�� */
                else
                {
                    return std::forward<T>(value);
                }
            }
#else
            /* C++ 11/14�� */
            /* std::string�^��const char*�ɕϊ� */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value> = nullptr>
            auto Convert(T&& value)
            {
                return std::forward<T>(value).c_str();
            }

            /* �񋓌^(enum/enum class)�����^�ɕϊ� */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            auto Convert(T&& value)
            {
                return std::forward<cpp_lib::type_traits::underlying_type_t<T>>(cpp_lib::type_traits::underlying_cast(value));
            }

            /* std::string�^�A�񋓌^(enum/enum class)�ȊO�́A���̂܂܏o�� */
            template<typename T, cpp_lib::type_traits::concept_t<!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value && !std::is_enum<T>::value> = nullptr>
            auto Convert(T&& value)
            {
                return std::forward<T>(value);
            }
#endif

            /* ������̃t�H�[�}�b�e�B���O(��������) */
            template<typename ... Args>
            std::string FormatInternal(const std::string& format, Args&& ... args)
            {
                /* �t�H�[�}�b�g��̕��������Z�o */
                int str_len = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args) ...);

                /* �t�H�[�}�b�g���s */
                if (str_len < 0)
                {
                    throw std::runtime_error("String Formatting Error : " + format);
                }
                else
                {
                    /* Nothing to do */
                }

                /* �o�b�t�@�T�C�Y���Z�o(������ + null�����T�C�Y) */
                size_t buffer_size = str_len + sizeof(char);

                /* �o�b�t�@�T�C�Y���������m�� */
                std::unique_ptr<char[]> buffer(new char[buffer_size]);

                /* ������̃t�H�[�}�b�g */
                std::snprintf(buffer.get(), buffer_size, format.c_str(), args ...);

                /* �������std::string�^�ɕϊ����ďo�� */
                return std::string(buffer.get(), buffer.get() + str_len);
            }
        }

        /* ������̃t�H�[�}�b�e�B���O */
        template<typename ... Args>
        std::string Format(const std::string& format, Args&& ... args)
        {
            /* �e�p�����[�^�̌^��ϊ����āA������̃t�H�[�}�b�e�B���O */
            return detail::FormatInternal(format, detail::Convert(std::forward<Args>(args)) ...);
        }
    }
}

/* Format String Macro Function */
#define STRING_FORMAT(...) cpp_lib::string::Format(__VA_ARGS__)