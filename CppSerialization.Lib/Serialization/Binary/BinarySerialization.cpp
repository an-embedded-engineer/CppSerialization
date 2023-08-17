#include "BinarySerialization.h"
#include "Endian.h"

namespace cpp_lib
{
    namespace serialization
    {
        /* シングルトンインスタンス取得 */
        BinarySerialization& BinarySerialization::GetInstance()
        {
            static BinarySerialization instance;
            return instance;
        }

        /* コンストラクタ */
        BinarySerialization::BinarySerialization()
            : m_CurrentEndian(cpp_lib::endian::GetEnvironmentEndian())
            , m_TargetEndian(cpp_lib::endian::EndianType::Network)
        {
            /* Nothing to do */
        }

        /* 論理型(bool)データサイズ算出 */
        void BinarySerialization::Calculate(const bool_t& in_data, size_t& out_size)
        {
            /* データ型のサイズを加算 */
            out_size += sizeof(bool_t);
        }

        /* 論理型(bool)シリアライズ */
        void BinarySerialization::Serialize(const bool_t& in_data, size_t& offset, Archive& out_archive)
        {
            /* 論理値をバイトデータに変換 */
            byte_t in_byte = in_data == false ? 0 : 1;

            /* バイトデータをアーカイブの指定オフセット位置に書き込み */
            out_archive.Write(in_byte, offset);
        }

        /* 論理型(bool)デシリアライズ */
        void BinarySerialization::Deserialize(const Archive& in_archive, size_t& offset, bool_t& out_data)
        {
            /* バイトデータ */
            byte_t out_byte = 0;

            /* アーカイブの指定オフセット位置からバイトデータ読み込み */
            in_archive.Read(out_byte, offset);

            /* 論理値に変換 */
            out_data = (out_byte == 0) ? false : true;
        }

        /* 文字列型データサイズ算出 */
        void BinarySerialization::Calculate(const string_t& in_data, size_t& out_size)
        {
            /* 要素数の型(size_t型)のデータサイズを加算 */
            out_size += sizeof(size_t);

            /* 要素数算出(文字列の長さ + null文字のサイズ) */
            size_t data_size = (in_data.size() + sizeof(char));

            /* 要素数を加算 */
            out_size += data_size;
        }

        /* 文字列型シリアライズ */
        void BinarySerialization::Serialize(const string_t& in_data, size_t& offset, Archive& out_archive)
        {
            /* 要素数算出(文字列の長さ + null文字のサイズ) */
            size_t data_size = (in_data.size() + sizeof(char));

            /* 要素数をシリアライズ */
            this->Serialize(data_size, offset, out_archive);

            /* 指定オフセット位置から文字列データ書き込み */
            out_archive.Write(in_data, offset);
        }

        /* 文字列型デシリアライズ */
        void BinarySerialization::Deserialize(const Archive& in_archive, size_t& offset, string_t& out_data)
        {
            /* 要素数 */
            size_t data_size = 0;

            /* 要素数をデシリアライズ */
            this->Deserialize(in_archive, offset, data_size);

            /* 指定オフセット位置から指定サイズ分文字列データ読み込み */
            in_archive.Read(out_data, offset, data_size);
        }
    }
}
