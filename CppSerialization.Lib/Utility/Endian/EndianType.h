#pragma once
#include <string>
#include <stdexcept>

namespace util
{
    namespace endian
    {
        /* �G���f�B�A���^�C�v */
        enum class EndianType
        {
            Big,                /* �r�b�O�G���f�B�A�� */
            Little,             /* ���g���G���f�B�A�� */
            Network = Big,      /* �l�b�g���[�N�o�C�g�I�[�_�[ = �r�b�O�G���f�B�A�� */
        };

        /* �G���f�B�A���^�C�v�𕶎���ɕϊ� */
        static std::string ToString(EndianType type)
        {
            switch (type)
            {
            case util::endian::EndianType::Big:
                return "Big";
            case util::endian::EndianType::Little:
                return "Little";
            default:
                throw std::invalid_argument("Invalid Endian Type : " + std::to_string(static_cast<int>(type)));
            }
        }
    }
}
