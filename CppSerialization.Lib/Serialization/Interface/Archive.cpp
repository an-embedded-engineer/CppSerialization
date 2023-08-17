#include "Archive.h"
#include "FatalException.h"
#include "StringFormat.h"

namespace serialization
{
    /* �R���X�g���N�^ */
    Archive::Archive()
        : m_Buffer()
        , m_Size(0)
    {
        /* Nothing to do */
    }

    /* �R���X�g���N�^(�������m�ۃT�C�Y�w��) */
    Archive::Archive(size_t size)
        : m_Buffer()
        , m_Size(0)
    {
        /* �f�[�^�o�b�t�@�������m�� */
        this->Reserve(size);
    }

    /* �f�X�g���N�^ */
    Archive::~Archive()
    {
        /* ��ԃ��Z�b�g(�f�[�^�o�b�t�@�������J��) */
        this->Reset();
    }

    /* �f�[�^�o�b�t�@�擾(���j�[�N�|�C���^�Q��) */
    const std::unique_ptr<byte_t[]>& Archive::GetData() const
    {
        return this->m_Buffer;
    }

    /* �f�[�^�o�b�t�@�擾(�|�C���^�Q��) */
    const byte_ptr_t Archive::GetDataPtr() const
    {
        return this->m_Buffer.get();
    }

    /* �f�[�^�o�b�t�@�T�C�Y�擾 */
    size_t Archive::GetSize() const
    {
        return this->m_Size;
    }

    /* �f�[�^�o�b�t�@�������m�� */
    void Archive::Reserve(size_t size)
    {
        /* �������m�ۍς݂̏ꍇ�͏�ԃ��Z�b�g */
        if (this->m_Buffer != nullptr)
        {
            this->Reset();
        }

        /* �f�[�^�o�b�t�@�T�C�Y�Z�b�g */
        this->m_Size = size;
        /* �f�[�^�o�b�t�@�������m�� */
        this->m_Buffer = std::make_unique<byte_t[]>(size);
    }

    /* ��ԃ��Z�b�g(�f�[�^�o�b�t�@�������J��) */
    void Archive::Reset()
    {
        /* �f�[�^�o�b�t�@���Z�b�g(�������J��) */
        this->m_Buffer.reset();
        this->m_Buffer = nullptr;

        /* �f�[�^�o�b�t�@�T�C�Y�N���A */
        this->m_Size = 0;
    }

    /* �w��I�t�Z�b�g�ʒu��1byte�f�[�^�������� */
    void Archive::Write(const byte_t& in_byte, size_t& offset)
    {
        /* �͈͊O�`�F�b�N */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* �w��I�t�Z�b�g�ʒu�Ƀf�[�^�Z�b�g */
        this->m_Buffer[offset] = in_byte;

        /* �I�t�Z�b�g���C���N�������g */
        offset += 1;
    }

    /* �w��I�t�Z�b�g�ʒu����1byte�f�[�^�ǂݍ��� */
    void Archive::Read(byte_t& out_byte, size_t& offset) const
    {
        /* �͈͊O�`�F�b�N */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* �w��I�t�Z�b�g�ʒu�̃f�[�^�ǂݍ��� */
        out_byte = this->m_Buffer[offset];

        /* �I�t�Z�b�g���C���N�������g */
        offset += 1;
    }

    /* �w��I�t�Z�b�g�ʒu���當����f�[�^�������� */
    void Archive::Write(const string_t& in_str, size_t& offset)
    {
        /* �͈͊O�`�F�b�N */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* ������̒����擾 */
        size_t text_len = in_str.length();

        /* �͈͊O�`�F�b�N(�I�t�Z�b�g���當����̏I�[ + null) */
        if ((offset + text_len + 1) > this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d text_len=%d size=%d", offset, text_len, this->m_Size));
        }

        /* �w��I�t�Z�b�g�ʒu���當������R�s�[ */
        memcpy(this->m_Buffer.get() + offset, in_str.c_str(), text_len);

        /* �����񒷕��I�t�Z�b�g */
        offset += text_len;

        /* �I�[��null�����Z�b�g */
        this->m_Buffer[offset] = '\0';

        /* �I�[(null����)�T�C�Y���I�t�Z�b�g */
        offset += 1;
    }

    /* �w��I�t�Z�b�g�ʒu����I�[(null�����܂�)������f�[�^�ǂݍ��� */
    void Archive::Read(string_t& out_str, size_t& offset) const
    {
        /* �͈͊O�`�F�b�N */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* �w��I�t�Z�b�g�ʒu����I�[�܂ł𕶎���Ƃ��Ď擾 */
        out_str = std::string(reinterpret_cast<const char*>(this->m_Buffer.get() + offset));

        /* ������̒����擾 */
        size_t text_len = out_str.length();

        /* �����񒷕� + �I�[(null����)�T�C�Y���I�t�Z�b�g */
        offset += (text_len + 1);
    }

    /* �w��I�t�Z�b�g�ʒu����w��T�C�Y��������f�[�^�ǂݍ��� */
    void Archive::Read(string_t& out_str, size_t& offset, size_t length) const
    {
        /* �͈͊O�`�F�b�N */
        if (offset >= this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d size=%d", offset, this->m_Size));
        }

        /* �͈͊O�`�F�b�N */
        if (offset + length > this->m_Size)
        {
            THROW_FATAL_EXCEPTION(STRING_FORMAT("Offset is out of range : offset=%d length=%d size=%d", offset, length, this->m_Size));
        }

        /* ������null���� */
        if (*reinterpret_cast<const char*>(this->m_Buffer.get() + offset + length - 1) == '\0')
        {
            /* �w��I�t�Z�b�g�ʒu����I�[�܂ł𕶎���Ƃ��Ď擾 */
            out_str = std::string(reinterpret_cast<const char*>(this->m_Buffer.get() + offset), length - 1);

            /* ������̒����擾 */
            size_t text_len = out_str.length();

            /* �f�[�^�T�C�Y�`�F�b�N */
            if ((text_len + 1) != length)
            {
                THROW_FATAL_EXCEPTION(STRING_FORMAT("Data Size unmatch : text_len=%d length=%d", (text_len + 1), length));
            }
        }
        else
        {
            /* �w��I�t�Z�b�g�ʒu����I�[�܂ł𕶎���Ƃ��Ď擾 */
            out_str = std::string(reinterpret_cast<const char*>(this->m_Buffer.get() + offset), length);

            /* ������̒����擾 */
            size_t text_len = out_str.length();

            /* �f�[�^�T�C�Y�`�F�b�N */
            if (text_len != length)
            {
                THROW_FATAL_EXCEPTION(STRING_FORMAT("Data Size unmatch : text_len=%d length=%d", text_len, length));
            }
        }

        /* �f�[�^�T�C�Y�T�C�Y���I�t�Z�b�g */
        offset += length;
    }
}
