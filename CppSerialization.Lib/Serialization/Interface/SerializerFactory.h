#pragma once
#include "Serializer.h"
#include "BinarySerializer.h"
#include "TextSerializer.h"

namespace serialization
{
    /* シリアライザファクトリクラス */
    template <typename T>
    class SerializerFactory
    {
    public:
        /* バイナリ形式のシリアライザ生成 */
        static Serializer<T>& CreateBinarySerializer()
        {
            static BinarySerializer<T> serializer;
            return serializer;
        }

        /* テキスト形式のシリアライザ生成 */
        static Serializer<T>& CreateTextSerializer()
        {
            static TextSerializer<T> serializer;
            return serializer;
        }
    };
}
