#pragma once
#include "ExceptionTypes.h"

#include <cstdint>
#include <vector>
#include <string>

namespace util
{
    namespace exception
    {
        /* スタックトレース情報 */
        struct StackTrace
        {
            /* トレース数 */
            size_t trace_size;

            /* トレースアドレスリスト */
            std::vector<util::exception::address_t> traces;

            /* トレースシンボルリスト */
            std::vector<std::string> symbols;
        };
    }
}
