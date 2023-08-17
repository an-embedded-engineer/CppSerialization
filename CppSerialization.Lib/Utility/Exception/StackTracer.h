#pragma once
#include "StackTrace.h"

#include <sstream>

namespace util
{
    namespace exception
    {
        /* �X�^�b�N�g���[�X�擾�N���X */
        class StackTracer
        {
        public:
            /* �X�^�b�N�g���[�X���擾 */
            static const util::exception::StackTrace GetStackTrace();

            /* �X�^�b�N�g���[�X�𕶎���X�g���[���Ƀ_���v */
            static void DumpStackTrace(std::stringstream& ss);
        };
    }
}
