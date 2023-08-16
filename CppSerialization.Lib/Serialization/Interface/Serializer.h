#pragma once
#include "Archive.h"

namespace serialization
{
    template <typename T>
    class Serializer
    {
    public:
        virtual void Serialize(const T& in_data, serialization::Archive& out_archive) = 0;

        virtual void Deserialize(const serialization::Archive& in_archive, T& out_data) = 0;
    };
}
