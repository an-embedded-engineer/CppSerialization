#include "Serializer.h"
#include "BinarySerialization.h"

namespace cpp_lib
{
    namespace serialization
    {
        /* バイナリ形式シリアライザクラス */
        template <typename T>
        class BinarySerializer : public Serializer<T>
        {
        public:
            /* テンプレートで指定されたデータ型をシリアライズしてアーカイブに変換 */
            void Serialize(const T& in_data, serialization::Archive& out_archive) override
            {
                /* バイナリ形式シリアライズクラスシングルトンインスタンス取得 */
                auto& binary_serialization = serialization::BinarySerialization::GetInstance();

                /* 入力データをシリアライズしてアーカイブに変換 */
                binary_serialization.Serialize(in_data, out_archive);
            }

            /* アーカイブをデシリアライズしてテンプレートで指定されたデータ型に変換 */
            void Deserialize(const serialization::Archive& in_archive, T& out_data) override
            {
                /* バイナリ形式シリアライズクラスシングルトンインスタンス取得 */
                auto& binary_serialization = serialization::BinarySerialization::GetInstance();

                /* アーカイブをデシリアライズして出力データに変換 */
                binary_serialization.Deserialize(in_archive, out_data);
            }
        };
    }
}
