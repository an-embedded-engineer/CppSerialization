#pragma once
#include "ExceptionTypes.h"

#include <cstdint>
#include <vector>
#include <string>

namespace cpp_lib
{
    namespace exception
    {
        /* スタックトレース情報 */
        struct StackTrace
        {
            /* トレース数 */
            size_t trace_size;

            /* トレースアドレスリスト */
            std::vector<cpp_lib::exception::address_t> traces;

            /* トレースシンボルリスト */
            std::vector<std::string> symbols;

            /* コンストラクタ */
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
