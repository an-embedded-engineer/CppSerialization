#include "BinaryConverter.h"

#if 0
namespace util
{
    namespace binary
    {
        void BinaryConverter::Convert(const bool_t& in_data, std::array<byte_t, 1>& out_bytes, bool swap)
        {
            util::binary::UInt8BinaryConversion conv{};

            conv.data = (in_data == false) ? 0 : 1;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const uint8_t& in_data, std::array<byte_t, 1>& out_bytes, bool swap)
        {
            util::binary::UInt8BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const uint16_t& in_data, std::array<byte_t, 2>& out_bytes, bool swap)
        {
            util::binary::UInt16BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const uint32_t& in_data, std::array<byte_t, 4>& out_bytes, bool swap)
        {
            util::binary::UInt32BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const uint64_t& in_data, std::array<byte_t, 8>& out_bytes, bool swap)
        {
            util::binary::UInt64BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const sint8_t& in_data, std::array<byte_t, 1>& out_bytes, bool swap)
        {
            util::binary::SInt8BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            for (size_t i = 0; i < size; i++)
            {
                size_t j = (size - 1) - i;

                out_bytes[i] = conv.byte[j];
            }
        }

        void BinaryConverter::Convert(const sint16_t& in_data, std::array<byte_t, 2>& out_bytes, bool swap)
        {
            util::binary::SInt16BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            for (size_t i = 0; i < size; i++)
            {
                size_t j = (size - 1) - i;

                out_bytes[i] = conv.byte[j];
            }
        }

        void BinaryConverter::Convert(const sint32_t& in_data, std::array<byte_t, 4>& out_bytes, bool swap)
        {
            util::binary::SInt32BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            for (size_t i = 0; i < size; i++)
            {
                size_t j = (size - 1) - i;

                out_bytes[i] = conv.byte[j];
            }
        }

        void BinaryConverter::Convert(const sint64_t& in_data, std::array<byte_t, 8>& out_bytes, bool swap)
        {
            util::binary::SInt64BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const float32_t& in_data, std::array<byte_t, 4>& out_bytes, bool swap)
        {
            util::binary::Float32BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const float64_t& in_data, std::array<byte_t, 8>& out_bytes, bool swap)
        {
            util::binary::Float64BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const float128_t& in_data, std::array<byte_t, 16>& out_bytes, bool swap)
        {
            util::binary::Float128BinaryConversion conv{};

            conv.data = in_data;

            size_t size = sizeof(in_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    out_bytes[i] = conv.byte[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    out_bytes[i] = conv.byte[i];
                }
            }
        }

        void BinaryConverter::Convert(const std::array<byte_t, 1>& in_bytes, bool_t& out_data, bool swap)
        {
            util::binary::UInt8BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = (conv.data == 0) ? false : true;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 1>& in_bytes, uint8_t& out_data, bool swap)
        {
            util::binary::UInt8BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 2>& in_bytes, uint16_t& out_data, bool swap)
        {
            util::binary::UInt16BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 4>& in_bytes, uint32_t& out_data, bool swap)
        {
            util::binary::UInt32BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 8>& in_bytes, uint64_t& out_data, bool swap)
        {
            util::binary::UInt64BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 1>& in_bytes, sint8_t& out_data, bool swap)
        {
            util::binary::SInt8BinaryConversion conv{};

            for (size_t i = 0; i < sizeof(out_data); i++)
            {
                conv.byte[i] = in_bytes[i];
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 2>& in_bytes, sint16_t& out_data, bool swap)
        {
            util::binary::SInt16BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 4>& in_bytes, sint32_t& out_data, bool swap)
        {
            util::binary::SInt32BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 8>& in_bytes, sint64_t& out_data, bool swap)
        {
            util::binary::SInt64BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 4>& in_bytes, float32_t& out_data, bool swap)
        {
            util::binary::Float32BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 8>& in_bytes, float64_t& out_data, bool swap)
        {
            util::binary::Float64BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }

        void BinaryConverter::Convert(const std::array<byte_t, 16>& in_bytes, float128_t& out_data, bool swap)
        {
            util::binary::Float128BinaryConversion conv{};

            size_t size = sizeof(out_data);

            if (swap == true)
            {
                for (size_t i = 0; i < size; i++)
                {
                    size_t j = (size - 1) - i;

                    conv.byte[i] = in_bytes[j];
                }
            }
            else
            {
                for (size_t i = 0; i < size; i++)
                {
                    conv.byte[i] = in_bytes[i];
                }
            }

            out_data = conv.data;
        }
    }
}
#endif
