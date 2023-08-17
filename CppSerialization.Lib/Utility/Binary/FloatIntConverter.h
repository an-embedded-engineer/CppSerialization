#pragma once
#include "TypeTraits.h"

#include <cstdint>

namespace util
{
    namespace binary
    {
        /* 浮動小数 <=> 整数変換器 */
        template <typename TF, typename TI, util::type_traits::concept_t<std::is_floating_point<TF>::value && std::is_integral<TI>::value> = nullptr>
        union FloatIntConversion
        {
            TF f_value; /* 浮動小数型データ */
            TI i_value; /* 整数型データ */
        };

        /* 浮動小数 <=> 整数変換クラス */
        template <typename TF, typename TI, util::type_traits::concept_t<std::is_floating_point<TF>::value&& std::is_integral<TI>::value> = nullptr>
        struct FloatIntConverter
        {
            /* 整数 => 浮動小数変換 */
            static TF ConvertToFloat(TI i_value)
            {
                /* 浮動小数 <=> 整数変換器 */
                FloatIntConversion<TF, TI> conv{};

                /* 整数値をセット */
                conv.i_value = i_value;

                /* 浮動小数値を取得 */
                return conv.f_value;
            }

            /* 浮動小数 => 整数変換 */
            static TI ConvertToInt(TF f_value)
            {
                /* 浮動小数 <=> 整数変換器 */
                FloatIntConversion<TF, TI> conv{};

                /* 浮動小数値をセット */
                conv.f_value = f_value;

                /* 整数値をセット */
                return conv.i_value;
            }
        };
    }
}
