#pragma once
#include "ExceptionTypes.h"

#include <string>
#include <vector>

namespace cpp_lib
{
    namespace exception
    {
        /* �o�b�N�g���[�X�����N���X */
        class BackTraceGenerator
        {
        public:
            /* �o�b�N�g���[�X&�V���{�����X�g���� */
            static void GenerateBackTraceAndSymbols(size_t& trace_size, std::vector<cpp_lib::exception::address_t>& traces, std::vector<std::string>& symbols);

            /* �o�b�N�g���[�X���� */
            static void GenerateBackTrace(size_t& trace_size, std::vector<cpp_lib::exception::address_t>& traces);

            /* �V���{�����X�g���� */
            static void GenerateBackTraceSymbols(const size_t& trace_size, const std::vector<cpp_lib::exception::address_t>& traces, std::vector<std::string>& symbols);
        };
    }
}