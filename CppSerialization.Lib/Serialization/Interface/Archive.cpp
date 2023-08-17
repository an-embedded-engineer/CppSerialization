#include "Archive.h"
#include "FatalException.h"
#include "StringFormat.h"

namespace serialization
{
    /* コンストラクタ */
    Archive::Archive()
        : m_Buffer()
        , m_Size(0)
    {
        /* Nothing to do */
    }

    /* コンストラクタ(メモリ確保サイズ指定) */
    Archive::Archive(size_t size)
        : m_Buffer()
        , m_Size(0)
    {
        /* データバッファメモリ確保 */
        this->Reserve(size);
    }

    /* デストラクタ */
    Archive::~Archive()
    {
        /* 状態リセット(データバッファメモリ開放) */
        this->Reset();
    }

    /* データバッファ取得(ユニークポインタ参照) */
    const std::unique_ptr<byte_t[]>& Archive::GetData() const
    {
        return this->m_Buffer;
    }

    /* データバッファ取得(ポインタ参照) */
    const byte_ptr_t Archive::GetDataPtr() const
    {
        return this->m_Buffer.get();
    }

    /* データバッファサイズ取得 */
    size_t Archive::GetSize() const
    {
        return this->m_Size;
    }

    /* データバッファメモリ確保 */
    void Archive::Reserve(size_t size)
    {
        /* メモリ確保済みの場合は状態リセット */
        if (this->m_Buffer != nullptr)
        {
            this->Reset();
        }

        /* データバッファサイズセット */
        this->m_Size = size;
        /* データバッファメモリ確保 */
        this->m_Buffer = std::make_unique<byte_t[]>(size);
    }

    /* 状態リセット(データバッファメモリ開放) */
    void Archive::Reset()
    {
        /* データバッファリセット(メモリ開放) */
        this->m_Buffer.reset();
        this->m_Buffer = nullptr;

        /* データバッファサイズクリア */
        this->m_Size = 0;
    }

    /* 指定オフセット位置に1byteデータ書き込み */
    void Archive::Write(const byte_t& in_byte, size_t& offset)
    {
        /* 範囲外チェック */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* 指定オフセット位置にデータセット */
        this->m_Buffer[offset] = in_byte;

        /* オフセットをインクリメント */
        offset += 1;
    }

    /* 指定オフセット位置から1byteデータ読み込み */
    void Archive::Read(byte_t& out_byte, size_t& offset) const
    {
        /* 範囲外チェック */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* 指定オフセット位置のデータ読み込み */
        out_byte = this->m_Buffer[offset];

        /* オフセットをインクリメント */
        offset += 1;
    }

    /* 指定オフセット位置から文字列データ書き込み */
    void Archive::Write(const string_t& in_str, size_t& offset)
    {
        /* 範囲外チェック */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* 文字列の長さ取得 */
        size_t text_len = in_str.length();

        /* 範囲外チェック(オフセットから文字列の終端 + null) */
        if ((offset + text_len + 1) > this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d text_len=%d size=%d", offset, text_len, this->m_Size));
        }

        /* 指定オフセット位置から文字列をコピー */
        memcpy(this->m_Buffer.get() + offset, in_str.c_str(), text_len);

        /* 文字列長分オフセット */
        offset += text_len;

        /* 終端にnull文字セット */
        this->m_Buffer[offset] = '\0';

        /* 終端(null文字)サイズ分オフセット */
        offset += 1;
    }

    /* 指定オフセット位置から終端(null文字まで)文字列データ読み込み */
    void Archive::Read(string_t& out_str, size_t& offset) const
    {
        /* 範囲外チェック */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* 指定オフセット位置から終端までを文字列として取得 */
        out_str = std::string(reinterpret_cast<const char*>(this->m_Buffer.get() + offset));

        /* 文字列の長さ取得 */
        size_t text_len = out_str.length();

        /* 文字列長文 + 終端(null文字)サイズ分オフセット */
        offset += (text_len + 1);
    }

    /* 指定オフセット位置から指定サイズ分文字列データ読み込み */
    void Archive::Read(string_t& out_str, size_t& offset, size_t length) const
    {
        /* 範囲外チェック */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* 範囲外チェック */
        if (offset + length > this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d length=%d size=%d", offset, length, this->m_Size));
        }

        /* 末尾がnull文字 */
        if (*reinterpret_cast<const char*>(this->m_Buffer.get() + offset + length - 1) == '\0')
        {
            /* 指定オフセット位置から終端までを文字列として取得 */
            out_str = std::string(reinterpret_cast<const char*>(this->m_Buffer.get() + offset), length - 1);

            /* 文字列の長さ取得 */
            size_t text_len = out_str.length();

            /* データサイズチェック */
            if ((text_len + 1) != length)
            {
                THROW_FATAL_EXCEPTION(STRING_FORMAT("Data Size unmatch : text_len=%d length=%d", (text_len + 1), length));
            }
        }
        else
        {
            /* 指定オフセット位置から終端までを文字列として取得 */
            out_str = std::string(reinterpret_cast<const char*>(this->m_Buffer.get() + offset), length);

            /* 文字列の長さ取得 */
            size_t text_len = out_str.length();

            /* データサイズチェック */
            if (text_len != length)
            {
                THROW_FATAL_EXCEPTION(STRING_FORMAT("Data Size unmatch : text_len=%d length=%d", text_len, length));
            }
        }

        /* データサイズサイズ分オフセット */
        offset += length;
    }
}
