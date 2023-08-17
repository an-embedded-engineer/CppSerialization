#pragma once
#include "TypeTraits.h"

#include <cstdint>

namespace util
{
    namespace binary
    {
        /* �������� <=> �����ϊ��� */
        template <typename TF, typename TI, util::type_traits::concept_t<std::is_floating_point<TF>::value && std::is_integral<TI>::value> = nullptr>
        union FloatIntConversion
        {
            TF f_value; /* ���������^�f�[�^ */
            TI i_value; /* �����^�f�[�^ */
        };

        /* �������� <=> �����ϊ��N���X */
        template <typename TF, typename TI, util::type_traits::concept_t<std::is_floating_point<TF>::value&& std::is_integral<TI>::value> = nullptr>
        struct FloatIntConverter
        {
            /* ���� => ���������ϊ� */
            static TF ConvertToFloat(TI i_value)
            {
                /* �������� <=> �����ϊ��� */
                FloatIntConversion<TF, TI> conv{};

                /* �����l���Z�b�g */
                conv.i_value = i_value;

                /* ���������l���擾 */
                return conv.f_value;
            }

            /* �������� => �����ϊ� */
            static TI ConvertToInt(TF f_value)
            {
                /* �������� <=> �����ϊ��� */
                FloatIntConversion<TF, TI> conv{};

                /* ���������l���Z�b�g */
                conv.f_value = f_value;

                /* �����l���Z�b�g */
                return conv.i_value;
            }
        };
    }
}
