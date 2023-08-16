#pragma once
#include "StackTrace.h"

namespace util
{
    namespace exception
    {
        /* Stack Tracerクラス宣言 */
        class StackTracer
        {
        public:
            /* スタックトレース情報取得 */
            static const util::exception::StackTrace GetStackTrace();
        };
    }
}
