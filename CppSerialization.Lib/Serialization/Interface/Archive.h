#pragma once
#include "CommonTypes.h"

#include <memory>

namespace cpp_lib
{
    namespace serialization
    {
        /* �A�[�J�C�u(�V���A���C�Y�f�[�^)�N���X */
        class Archive
        {
        public:
            /* �R���X�g���N�^ */
            Archive();

            /* �R���X�g���N�^(�������m�ۃT�C�Y�w��) */
            Archive(size_t size);

            /* �f�X�g���N�^ */
            ~Archive();

            /* �f�[�^�o�b�t�@�擾(���j�[�N�|�C���^�Q��) */
            const std::unique_ptr<byte_t[]>& GetData() const;

            /* �f�[�^�o�b�t�@�擾(�|�C���^�Q��) */
            const byte_ptr_t GetDataPtr() const;

            /* �f�[�^�o�b�t�@�T�C�Y�擾 */
            size_t GetSize() const;

            /* �f�[�^�o�b�t�@�������m�� */
            void Reserve(size_t size);

            /* ��ԃ��Z�b�g(�f�[�^�o�b�t�@�������J��) */
            void Reset();

            /* �w��I�t�Z�b�g�ʒu��1byte�f�[�^�������� */
            void Write(const byte_t& in_byte, size_t& offset);

            /* �w��I�t�Z�b�g�ʒu����1byte�f�[�^�ǂݍ��� */
            void Read(byte_t& out_byte, size_t& offset) const;

            /* �w��I�t�Z�b�g�ʒu���當����f�[�^�������� */
            void Write(const string_t& in_str, size_t& offset);

            /* �w��I�t�Z�b�g�ʒu����I�[(null�����܂�)������f�[�^�ǂݍ��� */
            void Read(string_t& out_str, size_t& offset) const;

            /* �w��I�t�Z�b�g�ʒu����w��T�C�Y��������f�[�^�ǂݍ��� */
            void Read(string_t& out_str, size_t& offset, size_t length) const;

            /* �w��I�t�Z�b�g�ʒu����o�C�g�z�񏑂����� */
            template<size_t N>
            void Write(const std::array<byte_t, N>& in_bytes, size_t& offset)
            {
                for (size_t i = 0; i < N; i++)
                {
                    this->m_Buffer[offset + i] = in_bytes[i];
                }
                offset += N;
            }

            /* �w��I�t�Z�b�g�ʒu����o�C�g�z��ǂݍ��� */
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
            /* �V���A���C�Y�f�[�^�������݃o�b�t�@ */
            std::unique_ptr<byte_t[]> m_Buffer;

            /* �f�[�^�o�b�t�@�T�C�Y */
            size_t m_Size;
        };
    }
}
