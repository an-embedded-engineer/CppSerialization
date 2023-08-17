#pragma once
#include "Archive.h"

namespace serialization
{
    /* シリアライザクラス */
    template <typename T>
    class Serializer
    {
    public:
        /* テンプレートで指定されたデータ型をシリアライズしてアーカイブに変換 */
        virtual void Serialize(const T& in_data, serialization::Archive& out_archive) = 0;

        /* アーカイブをデシリアライズしてテンプレートで指定されたデータ型に変換 */
        virtual void Deserialize(const serialization::Archive& in_archive, T& out_data) = 0;
    };
}
