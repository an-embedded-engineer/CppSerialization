#include "StackTracer.h"
#include "PlatformConfig.h"
#include "StringFormat.h"

#if PLATFORM_TYPE == PLATFORM_MSVC
#include "BackTraceGenerator.h"

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
#include "BackTraceGenerator.h"

/* シンボルのデマングル有効化 */
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
        /* スタックトレース情報取得 */
        const cpp_lib::exception::StackTrace StackTracer::GetStackTrace()
        {
#if PLATFORM_TYPE == PLATFORM_MSVC

            /* スタックトレース情報生成 */
            cpp_lib::exception::StackTrace stack_trace;

            /* バックトレースリスト&トレースシンボルリスト生成(シンボルリストはそのまま使用可能) */
            cpp_lib::exception::BackTraceGenerator::GenerateBackTraceAndSymbols(stack_trace.trace_size, stack_trace.traces, stack_trace.symbols);

            return stack_trace;

#elif PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX

            /* スタックトレース情報生成 */
            cpp_lib::exception::StackTrace stack_trace;

            /* トレースシンボルリスト */
            std::vector<std::string> raw_symbols = {};

            /* バックトレースリスト&トレースシンボルリスト生成(シンボルリストはマングリングされた状態) */
            cpp_lib::exception::BackTraceGenerator::GenerateBackTraceAndSymbols(stack_trace.trace_size, stack_trace.traces, raw_symbols);

            /* シンボルリストメモリ確保 */
            stack_trace.symbols.reserve(raw_symbols.size());

            /* トレースサイズ分ループ */
            for (size_t i = 0; i < raw_symbols.size(); i++)
            {
                /* シンボル情報を取得 */
                std::string raw_symbol_info = raw_symbols[i];

#if DEMANGLE_SYMBOL_ENABLED == 1
                /* シンボル情報を整形して取得 */
                std::string symbol_info = cpp_lib::exception::SymbolInfoGenerator::GenerateSymbolInfoText(raw_symbol_info);
#else
                /* シンボル情報をそのまま取得 */
                std::string symbol_info = raw_symbol_info;
#endif

                /* シンボル情報をシンボルリストに追加 */
                stack_trace.symbols.push_back(symbol_info);
            }

            return stack_trace;
#else

            /* 空のスタックトレース情報生成 */
            cpp_lib::exception::StackTrace stack_trace;
            stack_trace.trace_size = 0;
            staci_trace.traces.clear();
            stack_trace.symbols.clear();

            return stack_trace;
#endif
        }

        /* スタックトレースを文字列ストリームにダンプ */
        void StackTracer::DumpStackTrace(std::stringstream& ss)
        {
            /* スタックトレース情報を取得 */
            cpp_lib::exception::StackTrace stack_trace = cpp_lib::exception::StackTracer::GetStackTrace();

            /* スタックトレースをダンプ */
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
