#pragma once
#include "TypeTraits.h"
#include <cstdint>

namespace util
{
    namespace binary
    {
#if 0
        /* float32 ⇔ sint32変換器 */
        union Float32Int32Convert
        {
            float f_value;
            int32_t i_value;
        };

        /* float32 ⇔ uint32変換器 */
        union Float32UInt32Convert
        {
            float f_value;
            uint32_t i_value;
        };

        /* float64 ⇔ sint64変換器 */
        union Float64Int64Convert
        {
            double f_value;
            int64_t i_value;
        };

        /* float64 ⇔ uint64変換器 */
        union Float64UInt64Convert
        {
            double f_value;
            int64_t i_value;
        };
#endif

        template <typename TF, typename TI, util::type_traits::concept_t<std::is_floating_point<TF>::value && std::is_integral<TI>::value> = nullptr>
        union FloatIntConversion
        {
            TF f_value;
            TI i_value;
        };

        /* Float ⇔ Int Converter(デフォルト) */
        template <typename TF, typename TI>
        struct FloatIntConverter
        {
            static TF ConvertToFloat(TI i_value)
            {
                FloatIntConversion<TF, TI> conv{};

                conv.i_value = i_value;

                return conv.f_value;

            }

            static TI ConvertToInt(TF f_value)
            {
                FloatIntConversion<TF, TI> conv{};

                conv.f_value = f_value;

                return conv.i_value;
            }
        };

#if 0
        /* float32 ⇔ sint32 Converter */
        template <>
        struct FloatIntConverter<float, int32_t>
        {
            /* sint32 -> float32変換 */
            static float ConvertToFloat(int32_t value)
            {
                /* float32 ⇔ sint32変換器初期化 */
                Float32Int32Convert convert{};

                /* int値をセット */
                convert.i_value = value;

                /* float値を出力 */
                return convert.f_value;
            }

            /* float32 -> sint32変換 */
            static int32_t ConvertToInt(float value)
            {
                /* float32 ⇔ sint32変換器初期化 */
                Float32Int32Convert convert{};

                /* float値をセット */
                convert.f_value = value;

                /* int値を出力 */
                return convert.i_value;
            }
        };

        /* float32 ⇔ uint32 Converter */
        template <>
        struct FloatIntConverter<float, uint32_t>
        {
            /* uint32 -> float32変換 */
            static float ConvertToFloat(uint32_t value)
            {
                /* float32 ⇔ uint32変換器初期化 */
                Float32UInt32Convert convert{};

                /* int値をセット */
                convert.i_value = value;

                /* float値を出力 */
                return convert.f_value;
            }

            /* float32 -> uint32変換 */
            static uint32_t ConvertToInt(float value)
            {
                /* float32 ⇔ uint32変換器初期化 */
                Float32UInt32Convert convert{};

                /* float値をセット */
                convert.f_value = value;

                /* int値を出力 */
                return convert.i_value;
            }
        };

        /* float64 ⇔ sint64 Converter */
        template <>
        struct FloatIntConverter<double, int64_t>
        {
            /* sint64 -> float64変換 */
            static double ConvertToFloat(int64_t value)
            {
                /* float64 ⇔ sint64変換器初期化 */
                Float64Int64Convert convert{};

                /* int値をセット */
                convert.i_value = value;

                /* float値を出力 */
                return convert.f_value;
            }

            /* float64 -> sint64変換 */
            static int64_t ConvertToInt(double value)
            {
                /* float64 ⇔ sint64変換器初期化 */
                Float64Int64Convert convert{};

                /* float値をセット */
                convert.f_value = value;

                /* int値を出力 */
                return convert.i_value;
            }
        };

        /* float64 ⇔ uint64 Converter */
        template <>
        struct FloatIntConverter<double, uint64_t>
        {
            /* uint64 -> float64変換 */
            static double ConvertToFloat(uint64_t value)
            {
                /* float64 ⇔ uint64変換器初期化 */
                Float64UInt64Convert convert{};

                /* int値をセット */
                convert.i_value = value;

                /* float値を出力 */
                return convert.f_value;
            }

            /* float64 -> uint64変換 */
            static uint64_t ConvertToInt(double value)
            {
                /* float64 ⇔ uint64変換器初期化 */
                Float64UInt64Convert convert{};

                /* float値をセット */
                convert.f_value = value;

                /* int値を出力 */
                return convert.i_value;
            }
        };
#endif
    }
}
