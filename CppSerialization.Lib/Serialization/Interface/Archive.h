#pragma once
#include "CommonTypes.h"

#include <memory>

namespace cpp_lib
{
    namespace serialization
    {
        /* アーカイブ(シリアライズデータ)クラス */
        class Archive
        {
        public:
            /* コンストラクタ */
            Archive();

            /* コンストラクタ(メモリ確保サイズ指定) */
            Archive(size_t size);

            /* デストラクタ */
            ~Archive();

            /* データバッファ取得(ユニークポインタ参照) */
            const std::unique_ptr<byte_t[]>& GetData() const;

            /* データバッファ取得(ポインタ参照) */
            const byte_ptr_t GetDataPtr() const;

            /* データバッファサイズ取得 */
            size_t GetSize() const;

            /* データバッファメモリ確保 */
            void Reserve(size_t size);

            /* 状態リセット(データバッファメモリ開放) */
            void Reset();

            /* 指定オフセット位置に1byteデータ書き込み */
            void Write(const byte_t& in_byte, size_t& offset);

            /* 指定オフセット位置から1byteデータ読み込み */
            void Read(byte_t& out_byte, size_t& offset) const;

            /* 指定オフセット位置から文字列データ書き込み */
            void Write(const string_t& in_str, size_t& offset);

            /* 指定オフセット位置から終端(null文字まで)文字列データ読み込み */
            void Read(string_t& out_str, size_t& offset) const;

            /* 指定オフセット位置から指定サイズ分文字列データ読み込み */
            void Read(string_t& out_str, size_t& offset, size_t length) const;

            /* 指定オフセット位置からバイト配列書き込み */
            template<size_t N>
            void Write(const std::array<byte_t, N>& in_bytes, size_t& offset)
            {
                for (size_t i = 0; i < N; i++)
                {
                    this->m_Buffer[offset + i] = in_bytes[i];
                }
                offset += N;
            }

            /* 指定オフセット位置からバイト配列読み込み */
            template<size_t N>
            void Read(std::array<byte_t, N>& out_bytes, size_t& offset) const
            {
                for (size_t i = 0; i < N; i++)
                {
                    out_bytes[i] = this->m_Buffer[offset + i];
                }
                offset += N;
            }

        private:
            /* シリアライズデータ書き込みバッファ */
            std::unique_ptr<byte_t[]> m_Buffer;

            /* データバッファサイズ */
            size_t m_Size;
        };
    }
}
