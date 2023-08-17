#pragma once
#include "StackTrace.h"

#include <sstream>

namespace util
{
    namespace exception
    {
        /* スタックトレース取得クラス */
        class StackTracer
        {
        public:
            /* スタックトレース情報取得 */
            static const util::exception::StackTrace GetStackTrace();

            /* スタックトレースを文字列ストリームにダンプ */
            static void DumpStackTrace(std::stringstream& ss);
        };
    }
}
