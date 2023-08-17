#include "TextSerialization.h"

#include <iomanip>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#define TEXT_SERIALIZE_MODE_XML     (0)
#define TEXT_SERIALIZE_MODE_JSON    (1)

#define TEXT_SERIALIZE_MODE         (TEXT_SERIALIZE_MODE_XML)

namespace cpp_lib
{
    namespace serialization
    {
        /* �V���O���g���C���X�^���X�擾 */
        TextSerialization& TextSerialization::GetInstance()
        {
            static TextSerialization instance;
            return instance;
        }


        /* �_���^(bool)�f�[�^�T�C�Y�Z�o */
        void TextSerialization::Serialize(const bool_t& in_data, Node& out_node)
        {
            /* �c���[�m�[�h�ɒl��ǉ� */
            out_node.put_value(in_data);
        }

        /* �_���^(bool)�f�V���A���C�Y */
        void TextSerialization::Deserialize(const Node& in_node, bool_t& out_data)
        {
            /* �c���[�m�[�h����v�f�擾 */
            if (auto value = in_node.get_value_optional<bool_t>())
            {
                /* �c���[�m�[�h�v�f����l���擾 */
                out_data = value.get();
            }
            /* �v�f�擾���s���͗�O�n�o */
            else
            {
                THROW_APP_EXCEPTION("Value is nothing");
            }
        }

        /* ������^�V���A���C�Y */
        void TextSerialization::Serialize(const string_t& in_data, Node& out_node)
        {
            /* �c���[�m�[�h�ɒl��ǉ� */
            out_node.put_value(in_data);
        }

        /* ������^�f�V���A���C�Y */
        void TextSerialization::Deserialize(const Node& in_node, string_t& out_data)
        {
            /* �c���[�m�[�h����v�f�擾 */
            if (auto value = in_node.get_value_optional<string_t>())
            {
                /* �c���[�m�[�h�v�f����l���擾 */
                out_data = value.get();
            }
            /* �v�f�擾���s���͗�O�n�o */
            else
            {
                THROW_APP_EXCEPTION("Value is nothing");
            }
        }


        /* �V���A���C�Y�����c���[�m�[�h���e�L�X�g�ɕϊ����A�A�[�J�C�u�ɃZ�b�g */
        void TextSerialization::WriteText(const Node& in_root_node, serialization::Archive& out_archive)
        {
            /* ������X�g���[�� */
            std::stringstream ss;

            /* �C���f���g�T�C�Y */
            const int indent = 2;

#if TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_XML
            /* XML�������ݐݒ�(�C���f���g�����A�C���f���g�T�C�Y�A�G���R�[�f�B���O) */
            auto setting = boost::property_tree::xml_parser::xml_writer_make_settings<string_t>(' ', indent, boost::property_tree::xml_parser::widen<string_t>("utf-8"));

            /* XML�Ƃ��ĕ�����X�g���[���ɏ������� */
            boost::property_tree::write_xml(ss, in_root_node, setting);
#elif TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_JSON
            /* JSON�Ƃ��ĕ�����X�g���[���ɏ������� */
            boost::property_tree::write_json(ss, in_root_node);
#else
#error Invalid Serialize Mode TEXT_SERIALIZE_MODE
#endif

            /* ������ɕϊ� */
            string_t in_str = ss.str();

            /* �����񒷂��擾 */
            size_t text_len = in_str.length();

            /* �o�b�t�@�T�C�Y�Z�o(������ + �I�[����(null����)�T�C�Y) */
            size_t buffer_size = text_len + 1;

            /* �V���A���C�Y��̃f�[�^�T�C�Y�ŃA�[�J�C�u�̃f�[�^�o�b�t�@�������m�� */
            out_archive.Reserve(buffer_size);

            /* �I�t�Z�b�g������ */
            size_t offset = 0;

            /* �w��I�t�Z�b�g�ʒu���當����f�[�^�������� */
            out_archive.Write(in_str, offset);
        }

        /* �A�[�J�C�u���e�L�X�g�ɕϊ����A�c���[�m�[�h�ɕϊ� */
        void TextSerialization::ReadText(const serialization::Archive& in_archive, Node& out_root_node)
        {
            /* ������X�g���[�� */
            std::stringstream ss;

            /* �A�[�J�C�u�̃f�[�^�o�b�t�@(�|�C���^)�𕶎���X�g���[���ɒǉ� */
            ss << in_archive.GetDataPtr();

#if TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_XML
            /* ������X�g���[����XML�Ƃ��ăc���[�m�[�h�ɓǂݍ��� */
            boost::property_tree::read_xml(ss, out_root_node);
#elif TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_JSON
            /* ������X�g���[����JSON�Ƃ��ăc���[�m�[�h�ɓǂݍ��� */
            boost::property_tree::read_json(ss, out_root_node);
#else
#error Invalid Serialize Mode TEXT_SERIALIZE_MODE
#endif
        }

        /* ���������f�[�^(32bit)��16�i��������ɕϊ� */
        void TextSerialization::ToHexString(const float32_t& in_data, string_t& out_data)
        {
            /* ������X�g���[�� */
            std::stringstream ss;

            /* �������� <=> �����ϊ��� */
            cpp_lib::binary::FloatIntConverter<float32_t, uint32_t> converter;

            /* �������� => �����ϊ� */
            uint32_t int_data = converter.ConvertToInt(in_data);

            /* �ϊ�����������16�i��������Ƃ��ĕ�����X�g���[���ɒǉ� */
            ss << std::showbase;
            ss << std::setw(4);
            ss << std::hex << int_data;

            /* ������ɕϊ� */
            out_data = ss.str();
        }

        /* ���������f�[�^(64bit)��16�i��������ɕϊ� */
        void TextSerialization::ToHexString(const float64_t& in_data, string_t& out_data)
        {
            /* ������X�g���[�� */
            std::stringstream ss;

            /* �������� <=> �����ϊ��� */
            cpp_lib::binary::FloatIntConverter<float64_t, uint64_t> converter;

            /* �������� => �����ϊ� */
            uint64_t int_data = converter.ConvertToInt(in_data);

            /* �ϊ�����������16�i��������Ƃ��ĕ�����X�g���[���ɒǉ� */
            ss << std::showbase;
            ss << std::setw(8);
            ss << std::hex << int_data;

            /* ������ɕϊ� */
            out_data = ss.str();
        }

        /* 16�i��������𕂓�����(32bit)�f�[�^�ɕϊ� */
        void TextSerialization::FromHexString(const string_t& in_data, float32_t& out_data)
        {
            /* 16�i��������𐮐��ɕϊ� */
            uint32_t int_data = std::stoul(in_data, nullptr, 16);

            /* �������� <=> �����ϊ��� */
            cpp_lib::binary::FloatIntConverter<float32_t, uint32_t> converter;

            /* ���� => ���������ϊ� */
            out_data = converter.ConvertToFloat(int_data);
        }

        /* 16�i��������𕂓�����(64bit)�f�[�^�ɕϊ� */
        void TextSerialization::FromHexString(const string_t& in_data, float64_t& out_data)
        {
            /* 16�i��������𐮐��ɕϊ� */
            uint64_t int_data = std::stoull(in_data, nullptr, 16);

            /* �������� <=> �����ϊ��� */
            cpp_lib::binary::FloatIntConverter<float64_t, uint64_t> converter;

            /* ���� => ���������ϊ� */
            out_data = converter.ConvertToFloat(int_data);
        }
    }
}
