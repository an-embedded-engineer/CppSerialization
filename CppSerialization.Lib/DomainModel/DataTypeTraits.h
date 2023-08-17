#pragma once
#include "DomainModelDataTypes.h"

namespace dm
{
    /* �񋓃f�[�^�^���� */
    template <typename T>
    struct EnumDataTypeTraits;

    /* dm::EnumType1 */
    template <>
    struct EnumDataTypeTraits<dm::EnumType1>
    {
        /* �ŏ��l�擾 */
        static auto GetMinValue(){ return dm::EnumType1::ENUM_VALUE1; }

        /* �ő�l�擾 */
        static auto GetMaxValue(){ return dm::EnumType1::ENUM_VALUE3; }
    };

    /* dm::EnumMessage1 */
    template <>
    struct EnumDataTypeTraits<dm::EnumMessage1>
    {
        /* �ŏ��l�擾 */
        static auto GetMinValue(){ return dm::EnumMessage1::VALUE1; }

        /* �ő�l�擾 */
        static auto GetMaxValue(){ return dm::EnumMessage1::VALUE4; }
    };

    /* dm::EnumMessage2 */
    template <>
    struct EnumDataTypeTraits<dm::EnumMessage2>
    {
        /* �ŏ��l�擾 */
        static auto GetMinValue(){ return dm::EnumMessage2::ENUM_MSG2_VALUE1; }

        /* �ő�l�擾 */
        static auto GetMaxValue(){ return dm::EnumMessage2::ENUM_MSG2_VALUE5; }
    };


    /* �\���̃f�[�^�^���� */
    template <typename T>
    struct DataTypeTraits;

    /* dm::StrucMessage1 */
    template <>
    struct DataTypeTraits<dm::StrucMessage1>
    {
        /* �����o���^�v���Ŏ擾(�ύX�s��) */
        static auto GetMembersAsTuple(const dm::StrucMessage1& data)
        {
            return std::tie(data.bool_value, data.uint_value, data.float_value);
        }

        /* �����o���^�v���Ŏ擾(�ύX��) */
        static auto GetMembersAsTuple(dm::StrucMessage1& data)
        {
            return std::tie(data.bool_value, data.uint_value, data.float_value);
        }

        /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX�s��) */
        static auto GetNamedMembersAsTuple(const dm::StrucMessage1& data)
        {
            return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
        }

        /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX��) */
        static auto GetNamedMembersAsTuple(dm::StrucMessage1& data)
        {
            return std::make_tuple(std::tie("bool_value", data.bool_value), std::tie("uint_value", data.uint_value), std::tie("float_value", data.float_value));
        }
    };

    /* dm::StrucMessage2 */
    template <>
    struct DataTypeTraits<dm::StrucMessage2>
    {
        /* �����o���^�v���Ŏ擾(�ύX�s��) */
        static auto GetMembersAsTuple(const dm::StrucMessage2& data)
        {
            return std::tie(data.float_array, data.ulong_vec);
        }

        /* �����o���^�v���Ŏ擾(�ύX��) */
        static auto GetMembersAsTuple(dm::StrucMessage2& data)
        {
            return std::tie(data.float_array, data.ulong_vec);
        }

        /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX�s��) */
        static auto GetNamedMembersAsTuple(const dm::StrucMessage2& data)
        {
            return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
        }

        /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX��) */
        static auto GetNamedMembersAsTuple(dm::StrucMessage2& data)
        {
            return std::make_tuple(std::tie("float_array", data.float_array), std::tie("ulong_vec", data.ulong_vec));
        }
    };

    /* dm::StrucMessage3 */
    template <>
    struct DataTypeTraits<dm::StrucMessage3>
    {
        /* �����o���^�v���Ŏ擾(�ύX�s��) */
        static auto GetMembersAsTuple(const dm::StrucMessage3& data)
        {
            return std::tie(data.string_value, data.enum_str_map);
        }

        /* �����o���^�v���Ŏ擾(�ύX��) */
        static auto GetMembersAsTuple(dm::StrucMessage3& data)
        {
            return std::tie(data.string_value, data.enum_str_map);
        }

        /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX�s��) */
        static auto GetNamedMembersAsTuple(const dm::StrucMessage3& data)
        {
            return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
        }

        /* �����o�𖼑O�t���^�v���Ŏ擾(�ύX��) */
        static auto GetNamedMembersAsTuple(dm::StrucMessage3& data)
        {
            return std::make_tuple(std::tie("string_value", data.string_value), std::tie("enum_str_map", data.enum_str_map));
        }
    };
}
