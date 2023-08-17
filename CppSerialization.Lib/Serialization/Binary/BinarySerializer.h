#include "Serializer.h"
#include "BinarySerialization.h"

namespace cpp_lib
{
    namespace serialization
    {
        /* �o�C�i���`���V���A���C�U�N���X */
        template <typename T>
        class BinarySerializer : public Serializer<T>
        {
        public:
            /* �e���v���[�g�Ŏw�肳�ꂽ�f�[�^�^���V���A���C�Y���ăA�[�J�C�u�ɕϊ� */
            void Serialize(const T& in_data, serialization::Archive& out_archive) override
            {
                /* �o�C�i���`���V���A���C�Y�N���X�V���O���g���C���X�^���X�擾 */
                auto& binary_serialization = serialization::BinarySerialization::GetInstance();

                /* ���̓f�[�^���V���A���C�Y���ăA�[�J�C�u�ɕϊ� */
                binary_serialization.Serialize(in_data, out_archive);
            }

            /* �A�[�J�C�u���f�V���A���C�Y���ăe���v���[�g�Ŏw�肳�ꂽ�f�[�^�^�ɕϊ� */
            void Deserialize(const serialization::Archive& in_archive, T& out_data) override
            {
                /* �o�C�i���`���V���A���C�Y�N���X�V���O���g���C���X�^���X�擾 */
                auto& binary_serialization = serialization::BinarySerialization::GetInstance();

                /* �A�[�J�C�u���f�V���A���C�Y���ďo�̓f�[�^�ɕϊ� */
                binary_serialization.Deserialize(in_archive, out_data);
            }
        };
    }
}
