#include "BinarySerialization.h"
#include "Endian.h"

namespace cpp_lib
{
    namespace serialization
    {
        /* �V���O���g���C���X�^���X�擾 */
        BinarySerialization& BinarySerialization::GetInstance()
        {
            static BinarySerialization instance;
            return instance;
        }

        /* �R���X�g���N�^ */
        BinarySerialization::BinarySerialization()
            : m_CurrentEndian(cpp_lib::endian::GetEnvironmentEndian())
            , m_TargetEndian(cpp_lib::endian::EndianType::Network)
        {
            /* Nothing to do */
        }

        /* �_���^(bool)�f�[�^�T�C�Y�Z�o */
        void BinarySerialization::Calculate(const bool_t& in_data, size_t& out_size)
        {
            /* �f�[�^�^�̃T�C�Y�����Z */
            out_size += sizeof(bool_t);
        }

        /* �_���^(bool)�V���A���C�Y */
        void BinarySerialization::Serialize(const bool_t& in_data, size_t& offset, Archive& out_archive)
        {
            /* �_���l���o�C�g�f�[�^�ɕϊ� */
            byte_t in_byte = in_data == false ? 0 : 1;

            /* �o�C�g�f�[�^���A�[�J�C�u�̎w��I�t�Z�b�g�ʒu�ɏ������� */
            out_archive.Write(in_byte, offset);
        }

        /* �_���^(bool)�f�V���A���C�Y */
        void BinarySerialization::Deserialize(const Archive& in_archive, size_t& offset, bool_t& out_data)
        {
            /* �o�C�g�f�[�^ */
            byte_t out_byte = 0;

            /* �A�[�J�C�u�̎w��I�t�Z�b�g�ʒu����o�C�g�f�[�^�ǂݍ��� */
            in_archive.Read(out_byte, offset);

            /* �_���l�ɕϊ� */
            out_data = (out_byte == 0) ? false : true;
        }

        /* ������^�f�[�^�T�C�Y�Z�o */
        void BinarySerialization::Calculate(const string_t& in_data, size_t& out_size)
        {
            /* �v�f���̌^(size_t�^)�̃f�[�^�T�C�Y�����Z */
            out_size += sizeof(size_t);

            /* �v�f���Z�o(������̒��� + null�����̃T�C�Y) */
            size_t data_size = (in_data.size() + sizeof(char));

            /* �v�f�������Z */
            out_size += data_size;
        }

        /* ������^�V���A���C�Y */
        void BinarySerialization::Serialize(const string_t& in_data, size_t& offset, Archive& out_archive)
        {
            /* �v�f���Z�o(������̒��� + null�����̃T�C�Y) */
            size_t data_size = (in_data.size() + sizeof(char));

            /* �v�f�����V���A���C�Y */
            this->Serialize(data_size, offset, out_archive);

            /* �w��I�t�Z�b�g�ʒu���當����f�[�^�������� */
            out_archive.Write(in_data, offset);
        }

        /* ������^�f�V���A���C�Y */
        void BinarySerialization::Deserialize(const Archive& in_archive, size_t& offset, string_t& out_data)
        {
            /* �v�f�� */
            size_t data_size = 0;

            /* �v�f�����f�V���A���C�Y */
            this->Deserialize(in_archive, offset, data_size);

            /* �w��I�t�Z�b�g�ʒu����w��T�C�Y��������f�[�^�ǂݍ��� */
            in_archive.Read(out_data, offset, data_size);
        }
    }
}
