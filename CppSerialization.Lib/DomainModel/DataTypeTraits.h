#pragma once
#include "DomainModelDataTypes.h"

namespace dm
{
    /* 列挙データ型特性 */
    template <typename T>
    struct EnumDataTypeTraits;

    /* dm::EnumType1 */
    template <>
    struct EnumDataTypeTraits<dm::EnumType1>
    {
        /* 最小値取得 */
        static auto GetMinValue(){ return dm::EnumType1::ENUM_VALUE1; }

        /* 最大値取得 */
        static auto GetMaxValue(){ return dm::EnumType1::ENUM_VALUE3; }
    };

    /* dm::EnumMessage1 */
    template <>
    struct EnumDataTypeTraits<dm::EnumMessage1>
    {
        /* 最小値取得 */
        static auto GetMinValue(){ return dm::EnumMessage1::VALUE1; }

        /* 最大値取得 */
        static auto GetMaxValue(){ return dm::EnumMessage1::VALUE4; }
    };

    /* dm::EnumMessage2 */
    template <>
    struct EnumDataTypeTraits<dm::EnumMessage2>
    {
        /* 最小値取得 */
        static auto GetMinValue(){ return dm::EnumMessage2::ENUM_MSG2_VALUE1; }

        /* 最大値取得 */
        static auto GetMaxValue(){ return dm::EnumMessage2::ENUM_MSG2_VALUE5; }
    };


    /* 構造体データ型特性 */
    template <typename T>
    struct DataTypeTraits;

    /* dm::StrucMessage1 */
    template <>
    struct DataTypeTraits<dm::StrucMessage1>
    {
        /* メンバをタプルで取得(変更不可) */
        static auto GetMembersAsTuple(const dm::StrucMessage1& data)
        {
            return std::tie(data.bool_value, data.uint_value, data.float_value);
        }

        /* メンバをタプルで取得(変更可) */
        static auto GetMembersAsTuple(dm::StrucMessage1& data)
        {
            return std::tie(data.bool_value, data.uint_value, data.float_value);
        }

        /* メンバを名前付きタプルで取得(変更不可) */
        static auto GetNamedMembersAsTuple(const dm::StrucMessage1& data)
        {
            return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
        }

        /* メンバを名前付きタプルで取得(変更可) */
        static auto GetNamedMembersAsTuple(dm::StrucMessage1& data)
        {
            return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
        }
    };

    /* dm::StrucMessage2 */
    template <>
    struct DataTypeTraits<dm::StrucMessage2>
    {
        /* メンバをタプルで取得(変更不可) */
        static auto GetMembersAsTuple(const dm::StrucMessage2& data)
        {
            return std::tie(data.float_array, data.ulong_vec);
        }

        /* メンバをタプルで取得(変更可) */
        static auto GetMembersAsTuple(dm::StrucMessage2& data)
        {
            return std::tie(data.float_array, data.ulong_vec);
        }

        /* メンバを名前付きタプルで取得(変更不可) */
        static auto GetNamedMembersAsTuple(const dm::StrucMessage2& data)
        {
            return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
        }

        /* メンバを名前付きタプルで取得(変更可) */
        static auto GetNamedMembersAsTuple(dm::StrucMessage2& data)
        {
            return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
        }
    };

    /* dm::StrucMessage3 */
    template <>
    struct DataTypeTraits<dm::StrucMessage3>
    {
        /* メンバをタプルで取得(変更不可) */
        static auto GetMembersAsTuple(const dm::StrucMessage3& data)
        {
            return std::tie(data.string_value, data.enum_str_map);
        }

        /* メンバをタプルで取得(変更可) */
        static auto GetMembersAsTuple(dm::StrucMessage3& data)
        {
            return std::tie(data.string_value, data.enum_str_map);
        }

        /* メンバを名前付きタプルで取得(変更不可) */
        static auto GetNamedMembersAsTuple(const dm::StrucMessage3& data)
        {
            return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
        }

        /* メンバを名前付きタプルで取得(変更可) */
        static auto GetNamedMembersAsTuple(dm::StrucMessage3& data)
        {
            return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
        }
    };
}
