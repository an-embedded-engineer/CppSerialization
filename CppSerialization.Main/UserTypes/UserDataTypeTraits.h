#pragma once
#include "UserDataTypes.h"
#include "DataTypeTraits.h"

using namespace cpp_lib::type_traits;

/* app::EnumType1 */
template <>
struct EnumDataTypeTraits<app::EnumType1>
{
    /* �ŏ��l�擾 */
    static auto GetMinValue()
    {
        return app::EnumType1::ENUM_VALUE1;
    }

    /* �ő�l�擾 */
    static auto GetMaxValue()
    {
        return app::EnumType1::ENUM_VALUE3;
    }
};

/* app::EnumMessage1 */
template <>
struct EnumDataTypeTraits<app::EnumMessage1>
{
    /* �ŏ��l�擾 */
    static auto GetMinValue()
    {
        return app::EnumMessage1::VALUE1;
    }

    /* �ő�l�擾 */
    static auto GetMaxValue()
    {
        return app::EnumMessage1::VALUE4;
    }
};

/* app::EnumMessage2 */
template <>
struct EnumDataTypeTraits<app::EnumMessage2>
{
    /* �ŏ��l�擾 */
    static auto GetMinValue()
    {
        return app::EnumMessage2::ENUM_MSG2_VALUE1;
    }

    /* �ő�l�擾 */
    static auto GetMaxValue()
    {
        return app::EnumMessage2::ENUM_MSG2_VALUE5;
    }
};

/* app::StrucMessage1 */
template <>
struct DataTypeTraits<app::StrucMessage1>
{
    /* �����o���^�v���Ŏ擾(�ύX�s��) */
    static auto GetMembersAsTuple(const app::StrucMessage1& data)
    {
        return std::tie(data.bool_value, data.uint_value, data.float_value);
    }

    /* �����o���^�v���Ŏ擾(�ύX��) */
    static auto GetMembersAsTuple(app::StrucMessage1& data)
    {
        return std::tie(data.bool_value, data.uint_value, data.float_value);
    }

    /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX�s��) */
    static auto GetNamedMembersAsTuple(const app::StrucMessage1& data)
    {
        return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
    }

    /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX��) */
    static auto GetNamedMembersAsTuple(app::StrucMessage1& data)
    {
        return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
    }
};

/* app::StrucMessage2 */
template <>
struct DataTypeTraits<app::StrucMessage2>
{
    /* �����o���^�v���Ŏ擾(�ύX�s��) */
    static auto GetMembersAsTuple(const app::StrucMessage2& data)
    {
        return std::tie(data.float_array, data.ulong_vec);
    }

    /* �����o���^�v���Ŏ擾(�ύX��) */
    static auto GetMembersAsTuple(app::StrucMessage2& data)
    {
        return std::tie(data.float_array, data.ulong_vec);
    }

    /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX�s��) */
    static auto GetNamedMembersAsTuple(const app::StrucMessage2& data)
    {
        return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
    }

    /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX��) */
    static auto GetNamedMembersAsTuple(app::StrucMessage2& data)
    {
        return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
    }
};

/* app::StrucMessage3 */
template <>
struct DataTypeTraits<app::StrucMessage3>
{
    /* �����o���^�v���Ŏ擾(�ύX�s��) */
    static auto GetMembersAsTuple(const app::StrucMessage3& data)
    {
        return std::tie(data.string_value, data.enum_str_map);
    }

    /* �����o���^�v���Ŏ擾(�ύX��) */
    static auto GetMembersAsTuple(app::StrucMessage3& data)
    {
        return std::tie(data.string_value, data.enum_str_map);
    }

    /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX�s��) */
    static auto GetNamedMembersAsTuple(const app::StrucMessage3& data)
    {
        return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
    }

    /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX��) */
    static auto GetNamedMembersAsTuple(app::StrucMessage3& data)
    {
        return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
    }
};
