#pragma once
#include "TypeTraits.h"
#include <cstdint>

namespace util
{
    namespace binary
    {
#if 0
        /* float32 �� sint32�ϊ��� */
        union Float32Int32Convert
        {
            float f_value;
            int32_t i_value;
        };

        /* float32 �� uint32�ϊ��� */
        union Float32UInt32Convert
        {
            float f_value;
            uint32_t i_value;
        };

        /* float64 �� sint64�ϊ��� */
        union Float64Int64Convert
        {
            double f_value;
            int64_t i_value;
        };

        /* float64 �� uint64�ϊ��� */
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

        /* Float �� Int Converter(�f�t�H���g) */
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
        /* float32 �� sint32 Converter */
        template <>
        struct FloatIntConverter<float, int32_t>
        {
            /* sint32 -> float32�ϊ� */
            static float ConvertToFloat(int32_t value)
            {
                /* float32 �� sint32�ϊ��평���� */
                Float32Int32Convert convert{};

                /* int�l���Z�b�g */
                convert.i_value = value;

                /* float�l���o�� */
                return convert.f_value;
            }

            /* float32 -> sint32�ϊ� */
            static int32_t ConvertToInt(float value)
            {
                /* float32 �� sint32�ϊ��평���� */
                Float32Int32Convert convert{};

                /* float�l���Z�b�g */
                convert.f_value = value;

                /* int�l���o�� */
                return convert.i_value;
            }
        };

        /* float32 �� uint32 Converter */
        template <>
        struct FloatIntConverter<float, uint32_t>
        {
            /* uint32 -> float32�ϊ� */
            static float ConvertToFloat(uint32_t value)
            {
                /* float32 �� uint32�ϊ��평���� */
                Float32UInt32Convert convert{};

                /* int�l���Z�b�g */
                convert.i_value = value;

                /* float�l���o�� */
                return convert.f_value;
            }

            /* float32 -> uint32�ϊ� */
            static uint32_t ConvertToInt(float value)
            {
                /* float32 �� uint32�ϊ��평���� */
                Float32UInt32Convert convert{};

                /* float�l���Z�b�g */
                convert.f_value = value;

                /* int�l���o�� */
                return convert.i_value;
            }
        };

        /* float64 �� sint64 Converter */
        template <>
        struct FloatIntConverter<double, int64_t>
        {
            /* sint64 -> float64�ϊ� */
            static double ConvertToFloat(int64_t value)
            {
                /* float64 �� sint64�ϊ��평���� */
                Float64Int64Convert convert{};

                /* int�l���Z�b�g */
                convert.i_value = value;

                /* float�l���o�� */
                return convert.f_value;
            }

            /* float64 -> sint64�ϊ� */
            static int64_t ConvertToInt(double value)
            {
                /* float64 �� sint64�ϊ��평���� */
                Float64Int64Convert convert{};

                /* float�l���Z�b�g */
                convert.f_value = value;

                /* int�l���o�� */
                return convert.i_value;
            }
        };

        /* float64 �� uint64 Converter */
        template <>
        struct FloatIntConverter<double, uint64_t>
        {
            /* uint64 -> float64�ϊ� */
            static double ConvertToFloat(uint64_t value)
            {
                /* float64 �� uint64�ϊ��평���� */
                Float64UInt64Convert convert{};

                /* int�l���Z�b�g */
                convert.i_value = value;

                /* float�l���o�� */
                return convert.f_value;
            }

            /* float64 -> uint64�ϊ� */
            static uint64_t ConvertToInt(double value)
            {
                /* float64 �� uint64�ϊ��평���� */
                Float64UInt64Convert convert{};

                /* float�l���Z�b�g */
                convert.f_value = value;

                /* int�l���o�� */
                return convert.i_value;
            }
        };
#endif
    }
}
