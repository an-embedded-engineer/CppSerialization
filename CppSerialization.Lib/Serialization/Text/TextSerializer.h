#include "Serializer.h"
#include "TextSerialization.h"

namespace serialization
{
    /* テキスト形式シリアライザクラス */
    template <typename T>
    class TextSerializer : public Serializer<T>
    {
    public:
        /* テンプレートで指定されたデータ型をシリアライズしてアーカイブに変換 */
        void Serialize(const T& in_data, serialization::Archive& out_archive) override
        {
            /* テキスト形式シリアライズクラスシングルトンインスタンス取得 */
            auto& text_serialization = serialization::TextSerialization::GetInstance();

            /* ルートテキストセット */
            string_t name = "root";

            /* 入力データをシリアライズしてアーカイブに変換 */
            text_serialization.Serialize(in_data, name, out_archive);
        }

        /* アーカイブをデシリアライズしてテンプレートで指定されたデータ型に変換 */
        void Deserialize(const serialization::Archive& in_archive, T& out_data) override
        {
            /* テキスト形式シリアライズクラスシングルトンインスタンス取得 */
            auto& text_serialization = serialization::TextSerialization::GetInstance();

            /* ルートテキストセット */
            string_t name = "root";

            /* アーカイブをデシリアライズして出力データに変換 */
            text_serialization.Deserialize(in_archive, name, out_data);
        }
    };
}
