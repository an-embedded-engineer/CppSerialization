#pragma once
#include "ExceptionTypes.h"

#include <string>
#include <vector>

namespace cpp_lib
{
    namespace exception
    {
        /* バックトレース生成クラス */
        class BackTraceGenerator
        {
        public:
            /* バックトレース&シンボルリスト生成 */
            static void GenerateBackTraceAndSymbols(size_t& trace_size, std::vector<cpp_lib::exception::address_t>& traces, std::vector<std::string>& symbols);

            /* バックトレース生成 */
            static void GenerateBackTrace(size_t& trace_size, std::vector<cpp_lib::exception::address_t>& traces);

            /* シンボルリスト生成 */
            static void GenerateBackTraceSymbols(const size_t& trace_size, const std::vector<cpp_lib::exception::address_t>& traces, std::vector<std::string>& symbols);
        };
    }
}
