#pragma once
#include "Archive.h"

namespace serialization
{
    /* �V���A���C�U�N���X */
    template <typename T>
    class Serializer
    {
    public:
        /* �e���v���[�g�Ŏw�肳�ꂽ�f�[�^�^���V���A���C�Y���ăA�[�J�C�u�ɕϊ� */
        virtual void Serialize(const T& in_data, serialization::Archive& out_archive) = 0;

        /* �A�[�J�C�u���f�V���A���C�Y���ăe���v���[�g�Ŏw�肳�ꂽ�f�[�^�^�ɕϊ� */
        virtual void Deserialize(const serialization::Archive& in_archive, T& out_data) = 0;
    };
}
