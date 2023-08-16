#pragma once
#include <type_traits>

namespace util
{
    namespace type_traits
    {
        /* �^�R���Z�v�g���� */
        template<bool con>
        using concept_t = typename std::enable_if<con, std::nullptr_t>::type;

        /* �񋓌^(enum/enum class)�̊��^���擾 */
        template<typename T>
        using underlying_type_t = typename std::underlying_type<T>::type;

        /* �񋓌^(enum/enum class)�����^�ɃL���X�g */
        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        constexpr util::type_traits::underlying_type_t<T> underlying_cast(T e)
        {
            return static_cast<util::type_traits::underlying_type_t<T>>(e);
        }

        /* �_���^(bool) */
        template <typename T>
        struct is_bool : std::false_type {};

        template <>
        struct is_bool<bool> : std::true_type {};


        /* �_���^(bool)�ȊO�̎Z�p�^(����/��������) */
        template <typename T>
        struct is_nonbool_arithmetic : std::is_arithmetic<T> {};

        template <>
        struct is_nonbool_arithmetic<bool> : std::false_type {};


        /* �_���^(bool)�ȊO�̐����^ */
        template <typename T>
        struct is_nonbool_integral : std::is_integral<T> {};

        template <>
        struct is_nonbool_integral<bool> : std::false_type {};


        /* �Z�p�^(1byte�̂��̈ȊO)(bool/char/uchar/schar/int8_t/uint8_t�ȊO) */
        template <typename T>
        struct is_non_1byte_arithmetic : std::is_arithmetic<T> {};

        template <>
        struct is_non_1byte_arithmetic<bool> : std::false_type {};

        template <>
        struct is_non_1byte_arithmetic<char> : std::false_type {};

        template <>
        struct is_non_1byte_arithmetic<int8_t> : std::false_type {};

        template <>
        struct is_non_1byte_arithmetic<uint8_t> : std::false_type {};


        /* �����^(1byte�̂��̈ȊO)(bool/char/uchar/schar/int8_t/uint8_t�ȊO) */
        template <typename T>
        struct is_non_1byte_integral : std::is_integral<T> {};

        template <>
        struct is_non_1byte_integral<bool> : std::false_type {};

        template <>
        struct is_non_1byte_integral<char> : std::false_type {};

        template <>
        struct is_non_1byte_integral<int8_t> : std::false_type {};

        template <>
        struct is_non_1byte_integral<uint8_t> : std::false_type {};
    }
}
