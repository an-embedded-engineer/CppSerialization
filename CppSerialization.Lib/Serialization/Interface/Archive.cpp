#include "Archive.h"

namespace serialization
{
    Archive::Archive()
        : m_Buffer()
        , m_Size(0)
    {
    }

    Archive::Archive(size_t size)
        : m_Buffer()
        , m_Size(0)
    {
        this->Reserve(size);
    }

    Archive::~Archive()
    {
        this->Reset();
    }

    const std::unique_ptr<byte_t[]>& Archive::GetData() const
    {
        return this->m_Buffer;
    }

    const byte_ptr_t Archive::GetDataPtr() const
    {
        return this->m_Buffer.get();
    }

    size_t Archive::GetSize() const
    {
        return this->m_Size;
    }

    void Archive::Reserve(size_t size)
    {
        if (this->m_Buffer != nullptr)
        {
            this->Reset();
        }

        this->m_Size = size;
        this->m_Buffer = std::make_unique<byte_t[]>(size);
    }

    void Archive::Reset()
    {
        this->m_Buffer.reset();
        this->m_Buffer = nullptr;
        this->m_Size = 0;
    }

    void Archive::Write(const byte_t& in_byte, size_t& offset)
    {
        this->m_Buffer[offset] = in_byte;
        offset += 1;
    }

    void Archive::Read(byte_t& out_byte, size_t& offset) const
    {
        out_byte = this->m_Buffer[offset];
        offset += 1;
    }

    void Archive::Write(const string_t& in_str, size_t& offset)
    {
        size_t text_len = in_str.length();

        memcpy(this->m_Buffer.get() + offset, in_str.c_str(), text_len);

        this->m_Buffer[offset + text_len] = '\0';
    }

    void Archive::Read(string_t& out_str, size_t& offset) const
    {
        out_str = std::string(reinterpret_cast<const char*>(this->m_Buffer.get() + offset));
    }
}
