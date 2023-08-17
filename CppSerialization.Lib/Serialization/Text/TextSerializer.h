#include "Serializer.h"
#include "TextSerialization.h"

namespace serialization
{
    /* �e�L�X�g�`���V���A���C�U�N���X */
    template <typename T>
    class TextSerializer : public Serializer<T>
    {
    public:
        /* �e���v���[�g�Ŏw�肳�ꂽ�f�[�^�^���V���A���C�Y���ăA�[�J�C�u�ɕϊ� */
        void Serialize(const T& in_data, serialization::Archive& out_archive) override
        {
            /* �e�L�X�g�`���V���A���C�Y�N���X�V���O���g���C���X�^���X�擾 */
            auto& text_serialization = serialization::TextSerialization::GetInstance();

            /* ���[�g�e�L�X�g�Z�b�g */
            string_t name = "root";

            /* ���̓f�[�^���V���A���C�Y���ăA�[�J�C�u�ɕϊ� */
            text_serialization.Serialize(in_data, name, out_archive);
        }

        /* �A�[�J�C�u���f�V���A���C�Y���ăe���v���[�g�Ŏw�肳�ꂽ�f�[�^�^�ɕϊ� */
        void Deserialize(const serialization::Archive& in_archive, T& out_data) override
        {
            /* �e�L�X�g�`���V���A���C�Y�N���X�V���O���g���C���X�^���X�擾 */
            auto& text_serialization = serialization::TextSerialization::GetInstance();

            /* ���[�g�e�L�X�g�Z�b�g */
            string_t name = "root";

            /* �A�[�J�C�u���f�V���A���C�Y���ďo�̓f�[�^�ɕϊ� */
            text_serialization.Deserialize(in_archive, name, out_data);
        }
    };
}
