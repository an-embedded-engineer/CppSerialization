#pragma once
#include "CommonTypes.h"
#include "Endian.h"

#include <cstdint>
#include <array>

namespace util
{
    namespace binary
    {
#if 0
        union UInt8BinaryConversion
        {
            uint8_t data;
            byte_t  byte[1];
        };

        union UInt16BinaryConversion
        {
            uint16_t data;
            byte_t   byte[2];
        };

        union UInt32BinaryConversion
        {
            uint32_t data;
            byte_t   byte[4];
        };

        union UInt64BinaryConversion
        {
            uint64_t data;
            byte_t   byte[8];
        };

        union SInt8BinaryConversion
        {
            sint8_t data;
            byte_t  byte[1];
        };

        union SInt16BinaryConversion
        {
            sint16_t data;
            byte_t   byte[2];
        };

        union SInt32BinaryConversion
        {
            sint32_t data;
            byte_t   byte[4];
        };

        union SInt64BinaryConversion
        {
            sint64_t data;
            byte_t   byte[8];
        };

        union Float32BinaryConversion
        {
            float32_t data;
            byte_t    byte[4];
        };

        union Float64BinaryConversion
        {
            float64_t data;
            byte_t   byte[8];
        };

        union Float128BinaryConversion
        {
            float128_t data;
            byte_t     byte[16];
        };

#else
        template <typename T>
        union BinaryConversion
        {
            T       data;
            byte_t  byte[sizeof(T)];
        };

#endif

        class BinaryConverter
        {
        public:
            template <typename T>
            static void Convert(const util::endian::EndianType in_current_endian, const util::endian::EndianType in_target_endian, const T& in_data, std::array<byte_t, sizeof(T)>& out_bytes)
            {
                if (in_current_endian != in_target_endian)
                {
                    BinaryConverter::Convert(in_data, out_bytes, true);
                }
                else
                {
                    BinaryConverter::Convert(in_data, out_bytes, false);
                }
            }

            template <typename T>
            static void Convert(const util::endian::EndianType in_current_endian, const util::endian::EndianType in_target_endian, const std::array<byte_t, sizeof(T)>& in_bytes, T& out_data)
            {
                if (in_current_endian != in_target_endian)
                {
                    BinaryConverter::Convert(in_bytes, out_data, true);
                }
                else
                {
                    BinaryConverter::Convert(in_bytes, out_data, false);
                }
            }

        private:
#if 0
            static void Convert(const bool_t& in_data, std::array<byte_t, 1>& out_bytes, bool swap = false);
            static void Convert(const uint8_t& in_data, std::array<byte_t, 1>& out_bytes, bool swap = false);
            static void Convert(const uint16_t& in_data, std::array<byte_t, 2>& out_bytes, bool swap = false);
            static void Convert(const uint32_t& in_data, std::array<byte_t, 4>& out_bytes, bool swap = false);
            static void Convert(const uint64_t& in_data, std::array<byte_t, 8>& out_bytes, bool swap = false);
            static void Convert(const sint8_t& in_data, std::array<byte_t, 1>& out_bytes, bool swap = false);
            static void Convert(const sint16_t& in_data, std::array<byte_t, 2>& out_bytes, bool swap = false);
            static void Convert(const sint32_t& in_data, std::array<byte_t, 4>& out_bytes, bool swap = false);
            static void Convert(const sint64_t& in_data, std::array<byte_t, 8>& out_bytes, bool swap = false);
            static void Convert(const float32_t& in_data, std::array<byte_t, 4>& out_bytes, bool swap = false);
            static void Convert(const float64_t& in_data, std::array<byte_t, 8>& out_bytes, bool swap = false);
            static void Convert(const float128_t& in_data, std::array<byte_t, 16>& out_bytes, bool swap = false);

            static void Convert(const std::array<byte_t, 1>& in_bytes, bool_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 1>& in_bytes, uint8_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 2>& in_bytes, uint16_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 4>& in_bytes, uint32_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 8>& in_bytes, uint64_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 1>& in_bytes, sint8_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 2>& in_bytes, sint16_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 4>& in_bytes, sint32_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 8>& in_bytes, sint64_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 4>& in_bytes, float32_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 8>& in_bytes, float64_t& out_data, bool swap = false);
            static void Convert(const std::array<byte_t, 16>& in_bytes, float128_t& out_data, bool swap = false);
#else

            template <typename T>
            static void Convert(const T& in_data, std::array<byte_t, sizeof(T)>& out_bytes, bool swap = false)
            {
                util::binary::BinaryConversion<T> conv{};

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

            template <typename T>
            static void Convert(const std::array<byte_t, sizeof(T)>& in_bytes, T& out_data, bool swap = false)
            {
                util::binary::BinaryConversion<T> conv{};

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
#endif
        };
    }
}
