#include "StackTracer.h"
#include "PlatformConfig.h"
#include "StringFormat.h"

#if PLATFORM_TYPE == PLATFORM_MSVC
#include "BackTraceGenerator.h"

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
#include "BackTraceGenerator.h"

/* �V���{���̃f�}���O���L���� */
#define DEMANGLE_SYMBOL_ENABLED     (1)

#if DEMANGLE_SYMBOL_ENABLED == 1
#include "SymbolInfoGenerator.h"
#include "SymbolInfo.h"
#endif
#endif

#include <string>
#include <iomanip>
#include <iostream>

namespace cpp_lib
{
    namespace exception
    {
        /* �X�^�b�N�g���[�X���擾 */
        const cpp_lib::exception::StackTrace StackTracer::GetStackTrace()
        {
#if PLATFORM_TYPE == PLATFORM_MSVC

            /* �X�^�b�N�g���[�X��񐶐� */
            cpp_lib::exception::StackTrace stack_trace;

            /* �o�b�N�g���[�X���X�g&�g���[�X�V���{�����X�g����(�V���{�����X�g�͂��̂܂܎g�p�\) */
            cpp_lib::exception::BackTraceGenerator::GenerateBackTraceAndSymbols(stack_trace.trace_size, stack_trace.traces, stack_trace.symbols);

            return stack_trace;

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX

            /* �X�^�b�N�g���[�X��񐶐� */
            cpp_lib::exception::StackTrace stack_trace;

            /* �g���[�X�V���{�����X�g */
            std::vector<std::string> raw_symbols = {};

            /* �o�b�N�g���[�X���X�g&�g���[�X�V���{�����X�g����(�V���{�����X�g�̓}���O�����O���ꂽ���) */
            cpp_lib::exception::BackTraceGenerator::GenerateBackTraceAndSymbols(stack_trace.trace_size, stack_trace.traces, raw_symbols);

            /* �V���{�����X�g�������m�� */
            stack_trace.symbols.reserve(raw_symbols.size());

            /* �g���[�X�T�C�Y�����[�v */
            for (size_t i = 0; i < raw_symbols.size(); i++)
            {
                /* �V���{�������擾 */
                std::string raw_symbol_info = raw_symbols[i];

#if DEMANGLE_SYMBOL_ENABLED == 1
                /* �V���{�����𐮌`���Ď擾 */
                std::string symbol_info = cpp_lib::exception::SymbolInfoGenerator::GenerateSymbolInfoText(raw_symbol_info);
#else
                /* �V���{���������̂܂܎擾 */
                std::string symbol_info = raw_symbol_info;
#endif

                /* �V���{�������V���{�����X�g�ɒǉ� */
                stack_trace.symbols.push_back(symbol_info);
            }

            return stack_trace;
#else

            /* ��̃X�^�b�N�g���[�X��񐶐� */
            cpp_lib::exception::StackTrace stack_trace;
            stack_trace.trace_size = 0;
            staci_trace.traces.clear();
            stack_trace.symbols.clear();

            return stack_trace;
#endif
        }

        /* �X�^�b�N�g���[�X�𕶎���X�g���[���Ƀ_���v */
        void StackTracer::DumpStackTrace(std::stringstream& ss)
        {
            /* �X�^�b�N�g���[�X�����擾 */
            cpp_lib::exception::StackTrace stack_trace = cpp_lib::exception::StackTracer::GetStackTrace();

            /* �X�^�b�N�g���[�X���_���v */
            ss << "[Stack Traces] : " << std::endl;
            for (size_t i = 0; i < stack_trace.traces.size(); i++)
            {
                if (i != 0)
                {
                    ss << std::endl;
                }

                ss << "  ";
                ss << std::setw(16) << std::setfill('0') << std::hex << (uint64_t)stack_trace.traces[i];
                ss << " | ";
                if (i < stack_trace.symbols.size())
                {
                    ss << stack_trace.symbols[i];
                }
                else
                {
                    ss << "<Unknown Symbol>";
                }
            }
        }
    }
}
