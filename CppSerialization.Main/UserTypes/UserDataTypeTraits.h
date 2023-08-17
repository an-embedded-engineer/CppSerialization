#pragma once
#include "UserDataTypes.h"
#include "DataTypeTraits.h"

using namespace cpp_lib::type_traits;

/* app::EnumType1 */
template <>
struct EnumDataTypeTraits<app::EnumType1>
{
    /* 最小値取得 */
    static auto GetMinValue()
    {
        return app::EnumType1::ENUM_VALUE1;
    }

    /* 最大値取得 */
    static auto GetMaxValue()
    {
        return app::EnumType1::ENUM_VALUE3;
    }
};

/* app::EnumMessage1 */
template <>
struct EnumDataTypeTraits<app::EnumMessage1>
{
    /* 最小値取得 */
    static auto GetMinValue()
    {
        return app::EnumMessage1::VALUE1;
    }

    /* 最大値取得 */
    static auto GetMaxValue()
    {
        return app::EnumMessage1::VALUE4;
    }
};

/* app::EnumMessage2 */
template <>
struct EnumDataTypeTraits<app::EnumMessage2>
{
    /* 最小値取得 */
    static auto GetMinValue()
    {
        return app::EnumMessage2::ENUM_MSG2_VALUE1;
    }

    /* 最大値取得 */
    static auto GetMaxValue()
    {
        return app::EnumMessage2::ENUM_MSG2_VALUE5;
    }
};

/* app::StrucMessage1 */
template <>
struct DataTypeTraits<app::StrucMessage1>
{
    /* メンバをタプルで取得(変更不可) */
    static auto GetMembersAsTuple(const app::StrucMessage1& data)
    {
        return std::tie(data.bool_value, data.uint_value, data.float_value);
    }

    /* メンバをタプルで取得(変更可) */
    static auto GetMembersAsTuple(app::StrucMessage1& data)
    {
        return std::tie(data.bool_value, data.uint_value, data.float_value);
    }

    /* メンバを名前付きタプルで取得(変更不可) */
    static auto GetNamedMembersAsTuple(const app::StrucMessage1& data)
    {
        return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
    }

    /* メンバを名前付きタプルで取得(変更可) */
    static auto GetNamedMembersAsTuple(app::StrucMessage1& data)
    {
        return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
    }
};

/* app::StrucMessage2 */
template <>
struct DataTypeTraits<app::StrucMessage2>
{
    /* メンバをタプルで取得(変更不可) */
    static auto GetMembersAsTuple(const app::StrucMessage2& data)
    {
        return std::tie(data.float_array, data.ulong_vec);
    }

    /* メンバをタプルで取得(変更可) */
    static auto GetMembersAsTuple(app::StrucMessage2& data)
    {
        return std::tie(data.float_array, data.ulong_vec);
    }

    /* メンバを名前付きタプルで取得(変更不可) */
    static auto GetNamedMembersAsTuple(const app::StrucMessage2& data)
    {
        return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
    }

    /* メンバを名前付きタプルで取得(変更可) */
    static auto GetNamedMembersAsTuple(app::StrucMessage2& data)
    {
        return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
    }
};

/* app::StrucMessage3 */
template <>
struct DataTypeTraits<app::StrucMessage3>
{
    /* メンバをタプルで取得(変更不可) */
    static auto GetMembersAsTuple(const app::StrucMessage3& data)
    {
        return std::tie(data.string_value, data.enum_str_map);
    }

    /* メンバをタプルで取得(変更可) */
    static auto GetMembersAsTuple(app::StrucMessage3& data)
    {
        return std::tie(data.string_value, data.enum_str_map);
    }

    /* メンバを名前付きタプルで取得(変更不可) */
    static auto GetNamedMembersAsTuple(const app::StrucMessage3& data)
    {
        return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
    }

    /* メンバを名前付きタプルで取得(変更可) */
    static auto GetNamedMembersAsTuple(app::StrucMessage3& data)
    {
        return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
    }
};
