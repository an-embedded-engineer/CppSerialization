#include "Serializer.h"
#include "BinarySerialization.h"

namespace serialization
{
    template <typename T>
    class BinarySerializer : public Serializer<T>
    {
    public:
        void Serialize(const T& in_data, serialization::Archive& out_archive) override
        {
            auto& binary_serialization = serialization::BinarySerialization::GetInstance();

            binary_serialization.Serialize(in_data, out_archive);
        }

        void Deserialize(const serialization::Archive& in_archive, T& out_data) override
        {
            auto& binary_serialization = serialization::BinarySerialization::GetInstance();

            binary_serialization.Deserialize(in_archive, out_data);
        }
    };
}
