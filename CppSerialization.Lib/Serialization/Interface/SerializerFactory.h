#pragma once
#include "Serializer.h"
#include "BinarySerializer.h"
#include "TextSerializer.h"

namespace serialization
{
    /* �V���A���C�U�t�@�N�g���N���X */
    template <typename T>
    class SerializerFactory
    {
    public:
        /* �o�C�i���`���̃V���A���C�U���� */
        static Serializer<T>& CreateBinarySerializer()
        {
            static BinarySerializer<T> serializer;
            return serializer;
        }

        /* �e�L�X�g�`���̃V���A���C�U���� */
        static Serializer<T>& CreateTextSerializer()
        {
            static TextSerializer<T> serializer;
            return serializer;
        }
    };
}
