#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "Endian.h"

#include <cstdint>
#include <array>
#include <cassert>

namespace cpp_lib
{
    namespace binary
    {
        /* �e���v���[�g�Ŏw�肳�ꂽ�Z�p�^ <=> �o�C�i��(�o�C�g�z��)�ϊ��� */
        template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
        union BinaryConversion
        {
            T       data;               /* �o�C�i���ϊ��O�f�[�^ */
            byte_t  byte[sizeof(T)];    /* �o�C�i���ϊ���f�[�^(�o�C�g�z��) */
        };

        /* �Z�p�^ <=> �o�C�i��(�o�C�g�z��)�ϊ��N���X */
        class BinaryConverter
        {
        public:
            /* �e���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^���w�肳�ꂽ�G���f�B�A���Ńo�C�i��(�o�C�g�z��)�ɕϊ� */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const cpp_lib::endian::EndianType in_current_endian, const cpp_lib::endian::EndianType in_target_endian, const T& in_data, std::array<byte_t, sizeof(T)>& out_bytes)
            {
                /* ���݂̃G���f�B�A���ƃ^�[�Q�b�g�G���f�B�A�����قȂ�ꍇ */
                if (in_current_endian != in_target_endian)
                {
                    /* �e���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^���o�C�i��(�o�C�g�z��)�ɕϊ�(�X���b�v����) */
                    BinaryConverter::Convert(in_data, out_bytes, true);
                }
                else
                {
                    /* �e���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^���o�C�i��(�o�C�g�z��)�ɕϊ�(�X���b�v�Ȃ�) */
                    BinaryConverter::Convert(in_data, out_bytes, false);
                }
            }

            /* �o�C�i��(�o�C�g�z��)���w�肳�ꂽ�G���f�B�A���Ńe���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^�ɕϊ� */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const cpp_lib::endian::EndianType in_current_endian, const cpp_lib::endian::EndianType in_target_endian, const std::array<byte_t, sizeof(T)>& in_bytes, T& out_data)
            {
                /* ���݂̃G���f�B�A���ƃ^�[�Q�b�g�G���f�B�A�����قȂ�ꍇ */
                if (in_current_endian != in_target_endian)
                {
                    /* �o�C�i��(�o�C�g�z��)���e���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^�ɕϊ�(�X���b�v����) */
                    BinaryConverter::Convert(in_bytes, out_data, true);
                }
                else
                {
                    /* �o�C�i��(�o�C�g�z��)���e���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^�ɕϊ�(�X���b�v�Ȃ�) */
                    BinaryConverter::Convert(in_bytes, out_data, false);
                }
            }

        private:
            /* �e���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^���o�C�i��(�o�C�g�z��)�ɕϊ�(�X���b�v�L�����w��) */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const T& in_data, std::array<byte_t, sizeof(T)>& out_bytes, bool swap = false)
            {
                /* �e���v���[�g�Ŏw�肳�ꂽ�Z�p�^ <=> �o�C�i��(�o�C�g�z��)�ϊ��� */
                cpp_lib::binary::BinaryConversion<T> conv{};

                /* �Z�p�^�f�[�^�Z�b�g */
                conv.data = in_data;

                /* �f�[�^�T�C�Y�擾 */
                size_t size = out_bytes.size();

                /* �X���b�v���� */
                if (swap == true)
                {
                    /* �f�[�^�T�C�Y���o�C�g�z����t���ɃR�s�[ */
                    for (size_t i = 0; i < size; i++)
                    {
                        size_t j = (size - 1) - i;

                        out_bytes[i] = conv.byte[j];
                    }
                }
                /* �X���b�v�Ȃ� */
                else
                {
                    /* �f�[�^�T�C�Y���o�C�g�z����R�s�[ */
                    for (size_t i = 0; i < size; i++)
                    {
                        out_bytes[i] = conv.byte[i];
                    }
                }
            }

            /* �o�C�i��(�o�C�g�z��)���e���v���[�g�Ŏw�肳�ꂽ�Z�p�^�̃f�[�^�ɕϊ�(�X���b�v�L�����w��) */
            template <typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Convert(const std::array<byte_t, sizeof(T)>& in_bytes, T& out_data, bool swap = false)
            {
                /* �e���v���[�g�Ŏw�肳�ꂽ�Z�p�^ <=> �o�C�i��(�o�C�g�z��)�ϊ��� */
                cpp_lib::binary::BinaryConversion<T> conv{};

                /* �f�[�^�T�C�Y�擾 */
                size_t size = in_bytes.size();

                /* �X���b�v���� */
                if (swap == true)
                {
                    /* �f�[�^�T�C�Y���o�C�g�z����t���ɃR�s�[ */
                    for (size_t i = 0; i < size; i++)
                    {
                        size_t j = (size - 1) - i;

                        conv.byte[i] = in_bytes[j];
                    }
                }
                /* �X���b�v�Ȃ� */
                else
                {
                    /* �f�[�^�T�C�Y���o�C�g�z����R�s�[ */
                    for (size_t i = 0; i < size; i++)
                    {
                        conv.byte[i] = in_bytes[i];
                    }
                }

                /* �Z�p�^�f�[�^�ɕϊ����ďo�� */
                out_data = conv.data;
            }
        };
    }
}
