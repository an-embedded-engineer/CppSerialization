#pragma once
#include "Serializer.h"
#include "BinarySerializer.h"
#include "TextSerializer.h"

namespace serialization
{
    template <typename T>
    class SerializerFactory
    {
    public:
        static Serializer<T>& CreateBinarySerializer()
        {
            static BinarySerializer<T> serializer;
            return serializer;
        }

        static Serializer<T>& CreateTextSerializer()
        {
            static TextSerializer<T> serializer;
            return serializer;
        }
    };
}
