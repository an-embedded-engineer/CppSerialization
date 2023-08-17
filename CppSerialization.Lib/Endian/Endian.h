#pragma once
#include "EndianType.h"
#include "FloatIntConverter.h"

#include <type_traits>

namespace cpp_lib
{
    namespace endian
    {
        /* ���g���G���f�B�A������ */
        inline bool IsLittleEndian()
        {
            /* 0�r�b�g�ڂ��擪�ɗ��Ă��邩�ǂ����𔻒� : �擪�ɗ��Ă����烊�g���G���f�B�A�� */
            int data = 1;
            bool result = *reinterpret_cast<char*>(&data) == 1;
            return result;
        }

        /* �r�b�O�G���f�B�A������ */
        inline bool IsBigEndian()
        {
            /* ���g���G���f�B�A���łȂ���΃r�b�O�G���f�B�A�� */
            return !IsLittleEndian();
        }

        /* ���݂̎��s���̃G���f�B�A������ */
        inline cpp_lib::endian::EndianType GetEnvironmentEndian()
        {
            /* ���g���G���f�B�A������ */
            if (IsLittleEndian() == true)
            {
                return cpp_lib::endian::EndianType::Little;
            }
            else
            {
                return cpp_lib::endian::EndianType::Big;
            }
        }

        namespace detail
        {
            /* �o�C�g��X���b�v(�f�t�H���g) */
            template <typename T, size_t size>
            struct SwapBytes;

            /* �o�C�g��X���b�v(1byte) */
            template <typename T>
            struct SwapBytes<T, 1>
            {
                inline T operator()(T value)
                {
                    /* ���̂܂ܕԂ� */
                    return value;
                }
            };

            /* �o�C�g��X���b�v(2byte) */
            template <typename T>
            struct SwapBytes<T, 2>
            {
                inline T operator()(T value)
                {
                    /* �o�C�g����X���b�v */
                    return ((((value) & 0xFF00) >> 8)
                            | (((value) & 0x00FF) << 8));
                }
            };

            /* �o�C�g��X���b�v(4byte) */
            template <typename T>
            struct SwapBytes<T, 4>
            {
                inline T operator()(T value)
                {
                    /* �o�C�g����X���b�v */
                    return ((((value) & 0xFF000000) >> 24)
                            | (((value) & 0x00FF0000) >> 8)
                            | (((value) & 0x0000FF00) << 8)
                            | (((value) & 0x000000FF) << 24));
                }
            };

            /* �o�C�g��X���b�v(8byte) */
            template <typename T>
            struct SwapBytes<T, 8>
            {
                inline T operator()(T value)
                {
                    /* �o�C�g����X���b�v */
                    return ((((value) & 0xFF00000000000000ull) >> 56)
                            | (((value) & 0x00FF000000000000ull) >> 40)
                            | (((value) & 0x0000FF0000000000ull) >> 24)
                            | (((value) & 0x000000FF00000000ull) >> 8)
                            | (((value) & 0x00000000FF000000ull) << 8)
                            | (((value) & 0x0000000000FF0000ull) << 24)
                            | (((value) & 0x000000000000FF00ull) << 40)
                            | (((value) & 0x00000000000000FFull) << 56));
                }
            };

            /* �o�C�g��X���b�v(�P���x���������_) */
            template <>
            struct SwapBytes<float, 4>
            {
                inline float operator()(float value)
                {
                    /* uint32�^�ɕϊ����ăo�C�g����X���b�v */
                    uint32_t tmp_value = SwapBytes<uint32_t, sizeof(uint32_t)>()(cpp_lib::binary::FloatIntConverter<float, uint32_t>::ConvertToInt(value));

                    /* �X���b�v�����o�C�g���float�^�ɍēx�ϊ� */
                    return cpp_lib::binary::FloatIntConverter<float, uint32_t>::ConvertToFloat(tmp_value);
                }
            };

            /* �o�C�g��X���b�v(�{���x���������_) */
            template <>
            struct SwapBytes<double, 8>
            {
                inline double operator()(double value)
                {
                    /* uint64�^�ɕϊ����ăo�C�g����X���b�v */
                    uint64_t tmp_value = SwapBytes<uint64_t, sizeof(uint64_t)>()(cpp_lib::binary::FloatIntConverter<double, uint64_t>::ConvertToInt(value));

                    /* �X���b�v�����o�C�g���double�^�ɍēx�ϊ� */
                    return cpp_lib::binary::FloatIntConverter<double, uint64_t>::ConvertToFloat(tmp_value);
                }
            };

            /* �o�C�g��X���b�v(�G���f�B�A�����قȂ�ꍇ) */
            template<cpp_lib::endian::EndianType From, cpp_lib::endian::EndianType To, class T>
            struct Swap
            {
                inline T operator()(T value)
                {
                    /* �o�C�g����X���b�v */
                    return SwapBytes<T, sizeof(T)>()(value);
                }
            };

            /* �o�C�g��X���b�v(���g���G���f�B�A�����m) */
            template <class T>
            struct Swap<cpp_lib::endian::EndianType::Little, cpp_lib::endian::EndianType::Little, T>
            {
                inline T operator()(T value)
                {
                    /* ���̂܂ܕԂ� */
                    return value;
                }
            };

            /* �o�C�g��X���b�v(�r�b�O�G���f�B�A�����m) */
            template <class T>
            struct Swap<cpp_lib::endian::EndianType::Big, cpp_lib::endian::EndianType::Big, T>
            {
                inline T operator()(T value)
                {
                    /* ���̂܂ܕԂ� */
                    return value;
                }
            };
        }

        /* �o�C�g�X���b�v */
        template<cpp_lib::endian::EndianType From, cpp_lib::endian::EndianType To, class T>
        inline T ByteSwap(T value)
        {
            /* ���̓f�[�^�T�C�Y�`�F�b�N */
            static_assert((sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8), "(sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8)");

            /* ���̓f�[�^�^�`�F�b�N */
            static_assert((std::is_arithmetic<T>::value), "(std::is_arithmetic<T>::value)");

            /* �G���f�B�A���ϊ� */
            return detail::Swap<From, To, T>()(value);
        }

        /* �G���f�B�A���ϊ� */
        template<class T>
        inline T ConvertEndian(T value)
        {
            /* ���̓f�[�^�T�C�Y�`�F�b�N */
            static_assert((sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8), "(sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8)");

            /* ���̓f�[�^�^�`�F�b�N */
            static_assert((std::is_arithmetic<T>::value), "(std::is_arithmetic<T>::value)");

            /* ���g���G���f�B�A�� */
            if (GetEnvironmentEndian() == cpp_lib::endian::EndianType::Little)
            {
                /* �G���f�B�A���ϊ�(���g�� -> �r�b�O) */
                return detail::Swap<cpp_lib::endian::EndianType::Little, cpp_lib::endian::EndianType::Big, T>()(value);
            }
            else
            {
                /* �G���f�B�A���ϊ�(�r�b�O -> ���g��) */
                return detail::Swap<cpp_lib::endian::EndianType::Big, cpp_lib::endian::EndianType::Little, T>()(value);
            }
        }

        /* �G���f�B�A���ϊ� */
        template<class T, cpp_lib::endian::EndianType To>
        inline T ConvertEndian(T value)
        {
            /* ���̓f�[�^�T�C�Y�`�F�b�N */
            static_assert((sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8), "(sizeof(T) == 1) || (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8)");

            /* ���̓f�[�^�^�`�F�b�N */
            static_assert((std::is_arithmetic<T>::value), "(std::is_arithmetic<T>::value)");

            /* ���݂̊��̃G���f�B�A���Ǝw�肳�ꂽ�G���f�B�A�����قȂ� */
            if (GetEnvironmentEndian() != To)
            {
                /* ���݂̊��̃G���f�B�A�������g���G���f�B�A�� */
                if (GetEnvironmentEndian() == cpp_lib::endian::EndianType::Little)
                {
                    /* �G���f�B�A���ϊ�(���g�� -> �r�b�O) */
                    return detail::Swap<cpp_lib::endian::EndianType::Little, cpp_lib::endian::EndianType::Big, T>()(value);
                }
                /* ���݂̊��̃G���f�B�A�����r�b�O�G���f�B�A�� */
                else
                {
                    /* �G���f�B�A���ϊ�(�r�b�O -> ���g��) */
                    return detail::Swap<cpp_lib::endian::EndianType::Big, cpp_lib::endian::EndianType::Little, T>()(value);
                }
            }
            /* ���݂̊��̃G���f�B�A���Ǝw�肳�ꂽ�G���f�B�A�������� */
            else
            {
                /* �G���f�B�A���ϊ��s�v */
                return value;
            }
        }
    }
}
