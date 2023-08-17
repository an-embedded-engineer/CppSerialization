#pragma once
#include "ExceptionTypes.h"

#include <cstdint>
#include <vector>
#include <string>

namespace cpp_lib
{
    namespace exception
    {
        /* �X�^�b�N�g���[�X��� */
        struct StackTrace
        {
            /* �g���[�X�� */
            size_t trace_size;

            /* �g���[�X�A�h���X���X�g */
            std::vector<cpp_lib::exception::address_t> traces;

            /* �g���[�X�V���{�����X�g */
            std::vector<std::string> symbols;

            /* �R���X�g���N�^ */
            StackTrace()
                : trace_size(0)
                , traces()
                , symbols()
            {
                /* Nothing to do */
            }
        };
    }
}