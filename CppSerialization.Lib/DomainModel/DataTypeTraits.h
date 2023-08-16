#pragma once
#include "DomainModelDataTypes.h"

namespace dm
{
    /* Data Type Traits */
    template <typename T>
    struct DataTypeTraits;

    template <>
    struct DataTypeTraits<dm::StrucMessage1>
    {
        static auto GetMembersAsTuple(const dm::StrucMessage1& data)
        {
            return std::tie(data.bool_value, data.uint_value, data.float_value);
        }

        static auto GetMembersAsTuple(dm::StrucMessage1& data)
        {
            return std::tie(data.bool_value, data.uint_value, data.float_value);
        }

        static auto GetNamedMembersAsTuple(const dm::StrucMessage1& data)
        {
            return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
        }

        static auto GetNamedMembersAsTuple(dm::StrucMessage1& data)
        {
            return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
        }
    };

    template <>
    struct DataTypeTraits<dm::StrucMessage2>
    {
        static auto GetMembersAsTuple(const dm::StrucMessage2& data)
        {
            return std::tie(data.float_array, data.ulong_vec);
        }

        static auto GetMembersAsTuple(dm::StrucMessage2& data)
        {
            return std::tie(data.float_array, data.ulong_vec);
        }

        static auto GetNamedMembersAsTuple(const dm::StrucMessage2& data)
        {
            return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
        }

        static auto GetNamedMembersAsTuple(dm::StrucMessage2& data)
        {
            return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
        }
    };

    template <>
    struct DataTypeTraits<dm::StrucMessage3>
    {
        static auto GetMembersAsTuple(const dm::StrucMessage3& data)
        {
            return std::tie(data.string_value, data.enum_str_map);
        }

        static auto GetMembersAsTuple(dm::StrucMessage3& data)
        {
            return std::tie(data.string_value, data.enum_str_map);
        }

        static auto GetNamedMembersAsTuple(const dm::StrucMessage3& data)
        {
            return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
        }

        static auto GetNamedMembersAsTuple(dm::StrucMessage3& data)
        {
            return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
        }
    };

    /* Enum Data Type Traits */
    template <typename T>
    struct EnumDataTypeTraits;

    template <>
    struct EnumDataTypeTraits<dm::EnumType1>
    {
        static auto GetMinValue(){ return dm::EnumType1::ENUM_VALUE1; }

        static auto GetMaxValue(){ return dm::EnumType1::ENUM_VALUE3; }
    };

    template <>
    struct EnumDataTypeTraits<dm::EnumMessage1>
    {
        static auto GetMinValue(){ return dm::EnumMessage1::VALUE1; }

        static auto GetMaxValue(){ return dm::EnumMessage1::VALUE4; }
    };

    template <>
    struct EnumDataTypeTraits<dm::EnumMessage2>
    {
        static auto GetMinValue(){ return dm::EnumMessage2::ENUM_MSG2_VALUE1; }

        static auto GetMaxValue(){ return dm::EnumMessage2::ENUM_MSG2_VALUE5; }
    };

}
