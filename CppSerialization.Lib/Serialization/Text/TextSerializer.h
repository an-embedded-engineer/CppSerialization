#include "Serializer.h"
#include "TextSerialization.h"

namespace serialization
{
    template <typename T>
    class TextSerializer : public Serializer<T>
    {
    public:
        void Serialize(const T& in_data, serialization::Archive& out_archive) override
        {
            auto& text_serialization = serialization::TextSerialization::GetInstance();

            string_t name = "root";

            text_serialization.Serialize(in_data, name, out_archive);
        }

        void Deserialize(const serialization::Archive& in_archive, T& out_data) override
        {
            auto& text_serialization = serialization::TextSerialization::GetInstance();

            string_t name = "root";

            text_serialization.Deserialize(in_archive, name, out_data);
        }
    };
}
