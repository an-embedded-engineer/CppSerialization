#pragma once
#include "CommonTypes.h"

#include <array>
#include <vector>
#include <map>

namespace dm
{
    using BoolMessage = bool_t;

    using Int8Message = int8_t;

    using Int16Message = int16_t;

    using Int32Message = int32_t;

    using Int64Message = int64_t;

    using UInt8Message = uint8_t;

    using UInt16Message = uint16_t;

    using UInt32Message = uint32_t;

    using UInt64Message = uint64_t;

    using Float32Message = float32_t;

    using Float64Message = float64_t;

    using StringMessage = string_t;

    using ArrayMessage = std::array<int32_t, 4>;

    using VectorMessage = std::vector<float64_t>;

    using MapMessage = std::map<int32_t, float64_t>;

    enum class EnumMessage1
    {
        VALUE1,
        VALUE2,
        VALUE3,
        VALUE4,
    };

    enum EnumMessage2
    {
        ENUM_MSG2_VALUE1,
        ENUM_MSG2_VALUE2,
        ENUM_MSG2_VALUE3,
        ENUM_MSG2_VALUE4,
        ENUM_MSG2_VALUE5,
    };

    struct StrucMessage1
    {
        bool_t bool_value;
        uint32_t uint_value;
        float32_t float_value;
    };

    struct StrucMessage2
    {
        std::array<float32_t, 8> float_array;
        std::vector<uint64_t> ulong_vec;
    };

    enum class EnumType1
    {
        ENUM_VALUE1,
        ENUM_VALUE2,
        ENUM_VALUE3,
    };

    struct StrucMessage3
    {
        string_t string_value;
        std::map<EnumType1, string_t> enum_str_map;
    };
}
