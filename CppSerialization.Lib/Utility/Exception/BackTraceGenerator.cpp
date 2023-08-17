#include "BackTraceGenerator.h"
#include "PlatformConfig.h"

#if PLATFORM_TYPE == PLATFORM_MSVC
#include <Windows.h>
#include <ImageHlp.h>

#pragma comment(lib, "imagehlp.lib")
#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
#if PLATFORM_TYPE_OVERRIDE_ENABLED == 0
#include <execinfo.h>
#else
/* �o�b�N�g���[�X�擾�֐��X�^�u */
inline int backtrace(void** buffer, int size)
{
    return 0;
}

/* �o�b�N�g���[�X�V���{�����擾�֐��X�^�u */
inline char** backtrace_symbols(void* const* buffer, int size)
{
    return nullptr;
}
#endif
#endif

namespace util
{
    namespace exception
    {
        /* �o�b�N�g���[�X&�V���{�����X�g���� */
        void BackTraceGenerator::GenerateBackTraceAndSymbols(size_t& trace_size, std::vector<util::exception::address_t>& traces, std::vector<std::string>& symbols)
        {
            /* �ő�g���[�X�T�C�Y */
            constexpr size_t MaxSize = 256;

            /* �g���[�X���X�g */
            util::exception::address_t raw_traces[MaxSize] = {};

#if PLATFORM_TYPE == PLATFORM_MSVC
            /* ���݂̃v���Z�X���擾 */
            HANDLE process = GetCurrentProcess();

            /* �V���{���n���h���̏����� */
            SymInitialize(process, NULL, TRUE);

            /* �X�^�b�N�g���[�X�̎擾 */
            uint16_t raw_trace_size = CaptureStackBackTrace(0, MaxSize, raw_traces, NULL);

            /* �V���{�����ő�T�C�Y���Z�b�g */
            constexpr size_t MaxNameSize = 255;

            /* �V���{�����T�C�Y���Z�o */
            constexpr size_t SymbolInfoSize = sizeof(SYMBOL_INFO) + ((MaxNameSize + 1) * sizeof(char));

            /* �V���{�����̃������m�� */
            SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(SymbolInfoSize, 1);

            /* �V���{����񃁃����m�ې��� */
            if (symbol != nullptr)
            {
                /* �V���{�����ő�T�C�Y���Z�b�g */
                symbol->MaxNameLen = MaxNameSize;

                /* �V���{�����T�C�Y���Z�b�g */
                symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

                /* �g���[�X�T�C�Y���Z�b�g */
                trace_size = static_cast<size_t>(raw_trace_size);

                /* �g���[�X���X�g�̃������m�� */
                traces.reserve(trace_size);

                /* �V���{�����X�g�̃������m�� */
                symbols.reserve(trace_size);

                /* �g���[�X�T�C�Y�����[�v */
                for (size_t i = 0; i < trace_size; i++)
                {
                    /* �g���[�X�A�h���X���g���[�X���X�g�ɒǉ� */
                    traces.push_back(raw_traces[i]);

                    /* �g���[�X�A�h���X����V���{�������擾 */
                    SymFromAddr(process, (DWORD64)(raw_traces[i]), 0, symbol);

                    /* �V���{�������V���{�����X�g�ɒǉ� */
                    symbols.push_back(std::string(symbol->Name));
                }

                /* �V���{�����̃�������� */
                free(symbol);
            }
            else
            {
                /* �g���[�X�T�C�Y���Z�b�g */
                trace_size = static_cast<size_t>(raw_trace_size);

                /* �g���[�X���X�g�̃������m�� */
                traces.reserve(trace_size);

                /* �g���[�X�T�C�Y�����[�v */
                for (size_t i = 0; i < trace_size; i++)
                {
                    /* �g���[�X�A�h���X���g���[�X���X�g�ɒǉ� */
                    traces.push_back(raw_traces[i]);
                }

                /* �o�͗p�V���{�����X�g�Z�b�g  */
                symbols = std::vector<std::string>();
            }

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* �X�^�b�N�g���[�X�擾 */
            int raw_trace_size = backtrace(raw_traces, static_cast<int>(MaxSize));

            /* �V���{�����X�g�擾 */
            char** raw_symbols = backtrace_symbols(raw_traces, raw_trace_size);

            /* �g���[�X�T�C�Y�Z�b�g */
            trace_size = static_cast<size_t>(raw_trace_size);

            /* �o�͗p�g���[�X�A�h���X���X�g�������m�� */
            traces.reserve(trace_size);

            /* �o�͗p�V���{�����X�g�������m�� */
            symbols.reserve(trace_size);

            /* �g���[�X�T�C�Y�����[�v */
            for (size_t i = 0; i < trace_size; i++)
            {
                /* �o�͗p�g���[�X�A�h���X���X�g�Z�b�g */
                traces.push_back(traces[i]);

                /* �o�͗p�V���{�����X�g�Z�b�g */
                symbols.push_back(raw_symbols[i]);
            }

            /* �g���[�X�V���{�����X�g��� */
            free(raw_symbols);
#else
            /* �g���[�X�T�C�Y�N���A */
            trace_size = 0;
            /* �o�͗p�g���[�X�A�h���X���X�g�Z�b�g  */
            traces = std::vector<util::exception::address_t>();
            /* �o�͗p�V���{�����X�g�Z�b�g  */
            symbols = std::vector<std::string>();
#endif
        }

        /* �o�b�N�g���[�X���� */
        void BackTraceGenerator::GenerateBackTrace(size_t& trace_size, std::vector<util::exception::address_t>& traces)
        {
            /* �ő�g���[�X�T�C�Y */
            constexpr size_t MaxSize = 256;

            /* �g���[�X���X�g */
            util::exception::address_t raw_traces[MaxSize] = {};

#if PLATFORM_TYPE == PLATFORM_MSVC
            /* ���݂̃v���Z�X���擾 */
            HANDLE process = GetCurrentProcess();

            /* �V���{���n���h���̏����� */
            SymInitialize(process, NULL, TRUE);

            /* �X�^�b�N�g���[�X�̎擾 */
            uint16_t raw_trace_size = CaptureStackBackTrace(0, MaxSize, raw_traces, NULL);

            /* �g���[�X�T�C�Y���Z�b�g */
            trace_size = static_cast<size_t>(raw_trace_size);

            /* �g���[�X���X�g�̃������m�� */
            traces.reserve(trace_size);

            /* �g���[�X�T�C�Y�����[�v */
            for (size_t i = 0; i < trace_size; i++)
            {
                /* �g���[�X�A�h���X���g���[�X���X�g�ɒǉ� */
                traces.push_back(raw_traces[i]);
            }

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* �X�^�b�N�g���[�X�擾 */
            int raw_trace_size = backtrace(raw_traces, static_cast<int>(MaxSize));

            /* �g���[�X�T�C�Y�Z�b�g */
            trace_size = static_cast<size_t>(raw_trace_size);

            /* �o�͗p�g���[�X�A�h���X���X�g�������m�� */
            traces.reserve(trace_size);

            /* �o�͗p�g���[�X�A�h���X���X�g�Z�b�g */
            for (size_t i = 0; i < trace_size; i++)
            {
                traces.push_back(traces[i]);
            }
#else
            /* �g���[�X�T�C�Y�N���A */
            trace_size = 0;
            /* �o�͗p�g���[�X�A�h���X���X�g�Z�b�g  */
            traces = std::vector<util::exception::address_t>();
#endif
        }

        /* �V���{�����X�g���� */
        void BackTraceGenerator::GenerateBackTraceSymbols(const size_t& trace_size, const std::vector<util::exception::address_t>& traces, std::vector<std::string>& symbols)
        {
#if PLATFORM_TYPE == PLATFORM_MSVC
            /* ���݂̃v���Z�X���擾 */
            HANDLE process = GetCurrentProcess();

            /* �V���{���n���h���̏����� */
            SymInitialize(process, NULL, TRUE);

            /* �V���{�����ő�T�C�Y���Z�b�g */
            constexpr size_t MaxNameSize = 255;

            /* �V���{�����T�C�Y���Z�o */
            constexpr size_t SymbolInfoSize = sizeof(SYMBOL_INFO) + ((MaxNameSize + 1) * sizeof(char));

            /* �V���{�����̃������m�� */
            SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(SymbolInfoSize, 1);

            /* �V���{����񃁃����m�ې��� */
            if (symbol != nullptr)
            {
                /* �V���{�����ő�T�C�Y���Z�b�g */
                symbol->MaxNameLen = MaxNameSize;
                /* �V���{�����T�C�Y���Z�b�g */
                symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

                /* �V���{�����X�g�̃������m�� */
                symbols.reserve(trace_size);

                /* �g���[�X�T�C�Y�����[�v */
                for (size_t i = 0; i < trace_size; i++)
                {
                    /* �g���[�X�A�h���X����V���{�������擾 */
                    SymFromAddr(process, (DWORD64)(traces[i]), 0, symbol);

                    /* �V���{�������V���{�����X�g�ɒǉ� */
                    symbols.push_back(std::string(symbol->Name));
                }

                /* �V���{�����̃�������� */
                free(symbol);
            }
            else
            {
                /* �o�͗p�V���{�����X�g�Z�b�g  */
                symbols = std::vector<std::string>();
            }

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* �V���{�����X�g�擾 */
            char** raw_symbols = backtrace_symbols(traces.data(), static_cast<int>(trace_size));

            /* �o�͗p�V���{�����X�g�������m�� */
            symbols.reserve(trace_size);

            /* �o�͗p�V���{�����X�g�Z�b�g */
            for (size_t i = 0; i < trace_size; i++)
            {
                symbols.push_back(raw_symbols[i]);
            }

            /* �g���[�X�V���{�����X�g��� */
            free(raw_symbols);
#else
            /* �o�͗p�V���{�����X�g�Z�b�g  */
            symbols = std::vector<std::string>();
#endif
        }
    }
}
