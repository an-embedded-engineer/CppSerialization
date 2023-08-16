#pragma once
#include <string>

namespace util
{
    namespace exception
    {
        /* �V���{����� */
        struct SymbolInfo
        {
            /* �V���{�����L���t���O */
            bool is_valid;
            /* �I�u�W�F�N�g�� */
            std::string object_name;
            /* �A�h���X */
            std::string address;
            /* �}���O�����ꂽ�V���{���� */
            std::string mangled_symbol_name;
            /* �I�t�Z�b�g */
            std::string offset;

            /* �R���X�g���N�^ */
            SymbolInfo()
                : is_valid(false)
                , object_name("")
                , address("")
                , mangled_symbol_name("")
                , offset("")
            {
                /* Nothing to do */
            }
        };
    }
}
