#pragma once
#include "StackTrace.h"

namespace util
{
    namespace exception
    {
        /* Stack Tracer�N���X�錾 */
        class StackTracer
        {
        public:
            /* �X�^�b�N�g���[�X���擾 */
            static const util::exception::StackTrace GetStackTrace();
        };
    }
}
