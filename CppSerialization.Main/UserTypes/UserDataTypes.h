#pragma once
#include "CommonTypes.h"

#include <array>
#include <vector>
#include <map>

namespace app
{
    /* _^ */
    using BoolMessage = bool_t;

    /* tฎ^(8bit) */
    using Int8Message = int8_t;

    /* tฎ^(16bit) */
    using Int16Message = int16_t;

    /* tฎ^(32bit) */
    using Int32Message = int32_t;

    /* tฎ^(64bit) */
    using Int64Message = int64_t;

    /* ณฎ^(8bit) */
    using UInt8Message = uint8_t;

    /* ณฎ^(16bit) */
    using UInt16Message = uint16_t;

    /* ณฎ^(32bit) */
    using UInt32Message = uint32_t;

    /* ณฎ^(64bit) */
    using UInt64Message = uint64_t;

    /* ฎฌ^(32bit) */
    using Float32Message = float32_t;

    /* ฎฌ^(64bit) */
    using Float64Message = float64_t;

    /* ถ๑^ */
    using StringMessage = string_t;

    /* std::array^ */
    using ArrayMessage = std::array<int32_t, 4>;

    /* std::vector^ */
    using VectorMessage = std::vector<float64_t>;

    /* std::map^ */
    using MapMessage = std::map<int32_t, float64_t>;

    /* ๑^(enum class) */
    enum class EnumMessage1
    {
        VALUE1,
        VALUE2,
        VALUE3,
        VALUE4,
    };

    /* ๑^(enum) */
    enum EnumMessage2
    {
        ENUM_MSG2_VALUE1,
        ENUM_MSG2_VALUE2,
        ENUM_MSG2_VALUE3,
        ENUM_MSG2_VALUE4,
        ENUM_MSG2_VALUE5,
    };

    /* \ขฬ^1 */
    struct StrucMessage1
    {
        bool_t bool_value;
        uint32_t uint_value;
        float32_t float_value;
    };

    /* \ขฬ^2 */
    struct StrucMessage2
    {
        std::array<float32_t, 8> float_array;
        std::vector<uint64_t> ulong_vec;
    };

    /* ๑^(op) */
    enum class EnumType1
    {
        ENUM_VALUE1,
        ENUM_VALUE2,
        ENUM_VALUE3,
    };

    /* \ขฬ^3 */
    struct StrucMessage3
    {
        string_t string_value;
        std::map<EnumType1, string_t> enum_str_map;
    };
}
