#include "RandomDataGenerator.h"
#include "RandomGenerator.h"
#include <sstream>

#define MINUS_VALUE_ENABLED (0) /* 乱数データ生成時の負値有効化 */

namespace cpp_lib
{
    namespace random
    {
        /* 算術型用最大/最小値 */
#if MINUS_VALUE_ENABLED == 1
        constexpr int8_t    SInt8Min = -100;
        constexpr int8_t    SInt8Max = 100;
        constexpr int16_t   SInt16Min = -1000;
        constexpr int16_t   SInt16Max = 1000;
        constexpr int32_t   SInt32Min = -1000;
        constexpr int32_t   SInt32Max = 1000;
        constexpr int64_t   SInt64Min = -1000;
        constexpr int64_t   SInt64Max = 1000;
        constexpr uint8_t   UInt8Min = 0;
        constexpr uint8_t   UInt8Max = 200;
        constexpr uint16_t  UInt16Min = 0;
        constexpr uint16_t  UInt16Max = 2000;
        constexpr uint32_t  UInt32Min = 0;
        constexpr uint32_t  UInt32Max = 2000;
        constexpr uint64_t  UInt64Min = 0;
        constexpr uint64_t  UInt64Max = 2000;
        constexpr float32_t Float32Min = -1000.0f;
        constexpr float32_t Float32Max = 1000.0f;
        constexpr float64_t Float64Min = -1000.0;
        constexpr float64_t Float64Max = 1000.0;
#else
        constexpr int8_t    SInt8Min = 0;
        constexpr int8_t    SInt8Max = 100;
        constexpr int16_t   SInt16Min = 0;
        constexpr int16_t   SInt16Max = 1000;
        constexpr int32_t   SInt32Min = 0;
        constexpr int32_t   SInt32Max = 1000;
        constexpr int64_t   SInt64Min = 0;
        constexpr int64_t   SInt64Max = 1000;
        constexpr uint8_t   UInt8Min = 0;
        constexpr uint8_t   UInt8Max = 200;
        constexpr uint16_t  UInt16Min = 0;
        constexpr uint16_t  UInt16Max = 2000;
        constexpr uint32_t  UInt32Min = 0;
        constexpr uint32_t  UInt32Max = 2000;
        constexpr uint64_t  UInt64Min = 0;
        constexpr uint64_t  UInt64Max = 2000;
        constexpr float32_t Float32Min = 0.0f;
        constexpr float32_t Float32Max = 1000.0f;
        constexpr float64_t Float64Min = 0.0;
        constexpr float64_t Float64Max = 1000.0;
#endif

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
            /* 乱数データとして使用する文字リスト */
            const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

            /* 乱数データとして使用する文字リストの長さを取得 */
            const size_t chars_length = chars.length();

            /* 乱数データとして生成する文字列の長さをランダムに算出 */
            int data_length = GET_RANDOM_INT(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE);

            std::stringstream ss;

            /* 文字列の長さ分繰り返す */
            for (int i = 0; i < data_length; i++)
            {
                /* 乱数データとして使用する文字リストのインデックスをランダムに選出 */
                int index = GET_RANDOM_INT(0, static_cast<int>(chars_length - 1));

                /* 乱数データとして使用する文字リストの指定インデックスの文字を追加 */
                ss << chars[index];
            }

            /* 文字列に変換 */
            data = ss.str();
        }
    }
}
