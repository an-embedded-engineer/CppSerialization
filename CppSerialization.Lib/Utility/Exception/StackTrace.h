#pragma once
#include "ExceptionTypes.h"

#include <cstdint>
#include <vector>
#include <string>

namespace util
{
    namespace exception
    {
        /* �X�^�b�N�g���[�X��� */
        struct StackTrace
        {
            /* �g���[�X�� */
            size_t trace_size;

            /* �g���[�X�A�h���X���X�g */
            std::vector<util::exception::address_t> traces;

            /* �g���[�X�V���{�����X�g */
            std::vector<std::string> symbols;
        };
    }
}
