#include "RandomDataGenerator.h"
#include "RandomDataGenerator.hpp"
#include "DataTypeTraits.h"
#include "RandomGenerator.h"
#include <sstream>

#define MINUS_VALUE_ENABLED (0) /* 負値有効化 */

namespace debug
{
    /* 算術型用最大/最小値 */
#if MINUS_VALUE_ENABLED == 1
    constexpr int8_t    SInt8Min    = -100;
    constexpr int8_t    SInt8Max    = 100;
    constexpr int16_t   SInt16Min   = -1000;
    constexpr int16_t   SInt16Max   = 1000;
    constexpr int32_t   SInt32Min   = -1000;
    constexpr int32_t   SInt32Max   = 1000;
    constexpr int64_t   SInt64Min   = -1000;
    constexpr int64_t   SInt64Max   = 1000;
    constexpr uint8_t   UInt8Min    = 0;
    constexpr uint8_t   UInt8Max    = 200;
    constexpr uint16_t  UInt16Min   = 0;
    constexpr uint16_t  UInt16Max   = 2000;
    constexpr uint32_t  UInt32Min   = 0;
    constexpr uint32_t  UInt32Max   = 2000;
    constexpr uint64_t  UInt64Min   = 0;
    constexpr uint64_t  UInt64Max   = 2000;
    constexpr float32_t Float32Min  = -1000.0f;
    constexpr float32_t Float32Max  = 1000.0f;
    constexpr float64_t Float64Min  = -1000.0;
    constexpr float64_t Float64Max  = 1000.0;
#else
    constexpr int8_t    SInt8Min    = 0;
    constexpr int8_t    SInt8Max    = 100;
    constexpr int16_t   SInt16Min   = 0;
    constexpr int16_t   SInt16Max   = 1000;
    constexpr int32_t   SInt32Min   = 0;
    constexpr int32_t   SInt32Max   = 1000;
    constexpr int64_t   SInt64Min   = 0;
    constexpr int64_t   SInt64Max   = 1000;
    constexpr uint8_t   UInt8Min    = 0;
    constexpr uint8_t   UInt8Max    = 200;
    constexpr uint16_t  UInt16Min   = 0;
    constexpr uint16_t  UInt16Max   = 2000;
    constexpr uint32_t  UInt32Min   = 0;
    constexpr uint32_t  UInt32Max   = 2000;
    constexpr uint64_t  UInt64Min   = 0;
    constexpr uint64_t  UInt64Max   = 2000;
    constexpr float32_t Float32Min  = 0.0f;
    constexpr float32_t Float32Max  = 1000.0f;
    constexpr float64_t Float64Min  = 0.0;
    constexpr float64_t Float64Max  = 1000.0;
#endif

    /* 列挙体(enum/enum class)型乱数データ生成 */
    template<typename T, util::type_traits::concept_t<std::is_enum<T>::value>>
    void RandomDataGenerator::Generate(T& data)
    {
        util::type_traits::underlying_type_t<T> min_value = util::type_traits::underlying_cast<T>(dm::EnumDataTypeTraits<T>::GetMinValue());

        util::type_traits::underlying_type_t<T> max_value = util::type_traits::underlying_cast<T>(dm::EnumDataTypeTraits<T>::GetMaxValue());

        util::type_traits::underlying_type_t<T> underlying_data = GET_RANDOM_INT(min_value, max_value);

        data = static_cast<T>(underlying_data);
    }

    /* クラス/構造体(class/struct)型メンバ乱数データ生成 */
    template<typename T, util::type_traits::concept_t<std::is_class<T>::value>>
    void RandomDataGenerator::Generate(T& data)
    {
        auto tuple = dm::DataTypeTraits<T>::GetMembersAsTuple(data);

        RandomDataGenerator::GenerateTuple(tuple);
    }

    /* 論理型(bool)乱数データ生成 */
    void RandomDataGenerator::Generate(bool& data)
    {
        data = GET_RANDOM_BOOL();
    }

    /* 8bit符号付整数型(int8)乱数データ生成 */
    void RandomDataGenerator::Generate(int8_t& data)
    {
        data = GET_RANDOM_INT(SInt8Min, SInt8Max);
    }

    /* 16bit符号付整数型(int16)乱数データ生成 */
    void RandomDataGenerator::Generate(int16_t& data)
    {
        data = GET_RANDOM_INT(SInt16Min, SInt16Max);
    }

    /* 32bit符号付整数型(int32)乱数データ生成 */
    void RandomDataGenerator::Generate(int32_t& data)
    {
        data = GET_RANDOM_INT(SInt32Min, SInt32Max);
    }

    /* 64bit符号付整数型(int64)乱数データ生成 */
    void RandomDataGenerator::Generate(int64_t& data)
    {
        data = GET_RANDOM_INT(SInt64Min, SInt64Max);
    }

    /* 8bit符号無整数型(uint8)乱数データ生成 */
    void RandomDataGenerator::Generate(uint8_t& data)
    {
        data = GET_RANDOM_INT(UInt8Min, UInt8Max);
    }

    /* 16bit符号無整数型(uint16)乱数データ生成 */
    void RandomDataGenerator::Generate(uint16_t& data)
    {
        data = GET_RANDOM_INT(UInt16Min, UInt16Max);
    }

    /* 32bit符号無整数型(uint32)乱数データ生成 */
    void RandomDataGenerator::Generate(uint32_t& data)
    {
        data = GET_RANDOM_INT(UInt32Min, UInt32Max);
    }

    /* 64bit符号無整数型(uint64)乱数データ生成 */
    void RandomDataGenerator::Generate(uint64_t& data)
    {
        data = GET_RANDOM_INT(UInt64Min, UInt64Max);
    }

    /* 32bit浮動小数型(float)乱数データ生成 */
    void RandomDataGenerator::Generate(float32_t& data)
    {
        data = GET_RANDOM_FLOAT(Float32Min, Float32Max);
    }

    /* 32bit浮動小数型(double)乱数データ生成 */
    void RandomDataGenerator::Generate(float64_t& data)
    {
        data = GET_RANDOM_FLOAT(Float64Min, Float64Max);
    }

    /* 文字列型(string)乱数データ生成 */
    void RandomDataGenerator::Generate(std::string& data)
    {
        int num = GET_RANDOM_INT(1, 10);

        std::stringstream ss;

        for (int i = 0; i < num; i++)
        {
            ss << i;
        }

        data = ss.str();
    }
}
