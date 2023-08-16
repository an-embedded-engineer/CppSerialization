#pragma once
#include "CommonTypes.h"

#include <memory>

namespace serialization
{
    class Archive
    {
    public:
        Archive();

        Archive(size_t size);

        ~Archive();

        const std::unique_ptr<byte_t[]>& GetData() const;

        const byte_ptr_t GetDataPtr() const;

        size_t GetSize() const;

        void Reserve(size_t size);

        void Reset();

        void Write(const byte_t& in_byte, size_t& offset);

        void Read(byte_t& out_byte, size_t& offset) const;

        void Write(const string_t& in_str, size_t& offset);

        void Read(string_t& out_str, size_t& offset) const;

        template<size_t N>
        void Write(const std::array<byte_t, N>& in_bytes, size_t& offset)
        {
            for (size_t i = 0; i < N; i++)
            {
                this->m_Buffer[offset + i] = in_bytes[i];
            }
            offset += N;
        }

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
        std::unique_ptr<byte_t[]> m_Buffer;

        size_t m_Size;
    };
}
