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
/* バックトレース取得関数スタブ */
inline int backtrace(void** buffer, int size)
{
    return 0;
}

/* バックトレースシンボル情報取得関数スタブ */
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
        /* バックトレース&シンボルリスト生成 */
        void BackTraceGenerator::GenerateBackTraceAndSymbols(size_t& trace_size, std::vector<util::exception::address_t>& traces, std::vector<std::string>& symbols)
        {
            /* 最大トレースサイズ */
            constexpr size_t MaxSize = 256;

            /* トレースリスト */
            util::exception::address_t raw_traces[MaxSize] = {};

#if PLATFORM_TYPE == PLATFORM_MSVC
            /* 現在のプロセスを取得 */
            HANDLE process = GetCurrentProcess();

            /* シンボルハンドラの初期化 */
            SymInitialize(process, NULL, TRUE);

            /* スタックトレースの取得 */
            uint16_t raw_trace_size = CaptureStackBackTrace(0, MaxSize, raw_traces, NULL);

            /* シンボル名最大サイズをセット */
            constexpr size_t MaxNameSize = 255;

            /* シンボル情報サイズを算出 */
            constexpr size_t SymbolInfoSize = sizeof(SYMBOL_INFO) + ((MaxNameSize + 1) * sizeof(char));

            /* シンボル情報のメモリ確保 */
            SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(SymbolInfoSize, 1);

            /* シンボル情報メモリ確保成功 */
            if (symbol != nullptr)
            {
                /* シンボル名最大サイズをセット */
                symbol->MaxNameLen = MaxNameSize;

                /* シンボル情報サイズをセット */
                symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

                /* トレースサイズをセット */
                trace_size = static_cast<size_t>(raw_trace_size);

                /* トレースリストのメモリ確保 */
                traces.reserve(trace_size);

                /* シンボルリストのメモリ確保 */
                symbols.reserve(trace_size);

                /* トレースサイズ分ループ */
                for (size_t i = 0; i < trace_size; i++)
                {
                    /* トレースアドレスをトレースリストに追加 */
                    traces.push_back(raw_traces[i]);

                    /* トレースアドレスからシンボル情報を取得 */
                    SymFromAddr(process, (DWORD64)(raw_traces[i]), 0, symbol);

                    /* シンボル名をシンボルリストに追加 */
                    symbols.push_back(std::string(symbol->Name));
                }

                /* シンボル情報のメモリ解放 */
                free(symbol);
            }
            else
            {
                /* トレースサイズをセット */
                trace_size = static_cast<size_t>(raw_trace_size);

                /* トレースリストのメモリ確保 */
                traces.reserve(trace_size);

                /* トレースサイズ分ループ */
                for (size_t i = 0; i < trace_size; i++)
                {
                    /* トレースアドレスをトレースリストに追加 */
                    traces.push_back(raw_traces[i]);
                }

                /* 出力用シンボルリストセット  */
                symbols = std::vector<std::string>();
            }

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* スタックトレース取得 */
            int raw_trace_size = backtrace(raw_traces, static_cast<int>(MaxSize));

            /* シンボルリスト取得 */
            char** raw_symbols = backtrace_symbols(raw_traces, raw_trace_size);

            /* トレースサイズセット */
            trace_size = static_cast<size_t>(raw_trace_size);

            /* 出力用トレースアドレスリストメモリ確保 */
            traces.reserve(trace_size);

            /* 出力用シンボルリストメモリ確保 */
            symbols.reserve(trace_size);

            /* トレースサイズ分ループ */
            for (size_t i = 0; i < trace_size; i++)
            {
                /* 出力用トレースアドレスリストセット */
                traces.push_back(traces[i]);

                /* 出力用シンボルリストセット */
                symbols.push_back(raw_symbols[i]);
            }

            /* トレースシンボルリスト解放 */
            free(raw_symbols);
#else
            /* トレースサイズクリア */
            trace_size = 0;
            /* 出力用トレースアドレスリストセット  */
            traces = std::vector<util::exception::address_t>();
            /* 出力用シンボルリストセット  */
            symbols = std::vector<std::string>();
#endif
        }

        /* バックトレース生成 */
        void BackTraceGenerator::GenerateBackTrace(size_t& trace_size, std::vector<util::exception::address_t>& traces)
        {
            /* 最大トレースサイズ */
            constexpr size_t MaxSize = 256;

            /* トレースリスト */
            util::exception::address_t raw_traces[MaxSize] = {};

#if PLATFORM_TYPE == PLATFORM_MSVC
            /* 現在のプロセスを取得 */
            HANDLE process = GetCurrentProcess();

            /* シンボルハンドラの初期化 */
            SymInitialize(process, NULL, TRUE);

            /* スタックトレースの取得 */
            uint16_t raw_trace_size = CaptureStackBackTrace(0, MaxSize, raw_traces, NULL);

            /* トレースサイズをセット */
            trace_size = static_cast<size_t>(raw_trace_size);

            /* トレースリストのメモリ確保 */
            traces.reserve(trace_size);

            /* トレースサイズ分ループ */
            for (size_t i = 0; i < trace_size; i++)
            {
                /* トレースアドレスをトレースリストに追加 */
                traces.push_back(raw_traces[i]);
            }

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* スタックトレース取得 */
            int raw_trace_size = backtrace(raw_traces, static_cast<int>(MaxSize));

            /* トレースサイズセット */
            trace_size = static_cast<size_t>(raw_trace_size);

            /* 出力用トレースアドレスリストメモリ確保 */
            traces.reserve(trace_size);

            /* 出力用トレースアドレスリストセット */
            for (size_t i = 0; i < trace_size; i++)
            {
                traces.push_back(traces[i]);
            }
#else
            /* トレースサイズクリア */
            trace_size = 0;
            /* 出力用トレースアドレスリストセット  */
            traces = std::vector<util::exception::address_t>();
#endif
        }

        /* シンボルリスト生成 */
        void BackTraceGenerator::GenerateBackTraceSymbols(const size_t& trace_size, const std::vector<util::exception::address_t>& traces, std::vector<std::string>& symbols)
        {
#if PLATFORM_TYPE == PLATFORM_MSVC
            /* 現在のプロセスを取得 */
            HANDLE process = GetCurrentProcess();

            /* シンボルハンドラの初期化 */
            SymInitialize(process, NULL, TRUE);

            /* シンボル名最大サイズをセット */
            constexpr size_t MaxNameSize = 255;

            /* シンボル情報サイズを算出 */
            constexpr size_t SymbolInfoSize = sizeof(SYMBOL_INFO) + ((MaxNameSize + 1) * sizeof(char));

            /* シンボル情報のメモリ確保 */
            SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(SymbolInfoSize, 1);

            /* シンボル情報メモリ確保成功 */
            if (symbol != nullptr)
            {
                /* シンボル名最大サイズをセット */
                symbol->MaxNameLen = MaxNameSize;
                /* シンボル情報サイズをセット */
                symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

                /* シンボルリストのメモリ確保 */
                symbols.reserve(trace_size);

                /* トレースサイズ分ループ */
                for (size_t i = 0; i < trace_size; i++)
                {
                    /* トレースアドレスからシンボル情報を取得 */
                    SymFromAddr(process, (DWORD64)(traces[i]), 0, symbol);

                    /* シンボル名をシンボルリストに追加 */
                    symbols.push_back(std::string(symbol->Name));
                }

                /* シンボル情報のメモリ解放 */
                free(symbol);
            }
            else
            {
                /* 出力用シンボルリストセット  */
                symbols = std::vector<std::string>();
            }

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* シンボルリスト取得 */
            char** raw_symbols = backtrace_symbols(traces.data(), static_cast<int>(trace_size));

            /* 出力用シンボルリストメモリ確保 */
            symbols.reserve(trace_size);

            /* 出力用シンボルリストセット */
            for (size_t i = 0; i < trace_size; i++)
            {
                symbols.push_back(raw_symbols[i]);
            }

            /* トレースシンボルリスト解放 */
            free(raw_symbols);
#else
            /* 出力用シンボルリストセット  */
            symbols = std::vector<std::string>();
#endif
        }
    }
}
