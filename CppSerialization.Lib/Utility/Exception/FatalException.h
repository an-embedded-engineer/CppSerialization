#pragma once
#include "ExceptionBase.h"

#include <string>

namespace util
{
    namespace exception
    {
        /* �v���I��O�N���X */
        class FatalException : public util::exception::ExceptionBase
        {
        public:
            /* �R���X�g���N�^ */
            FatalException(const std::string& message);

            /* �R���X�g���N�^ */
            FatalException(const std::string& message, const std::string& file, const std::string& func, const int line);

            /* �f�X�g���N�^ */
            virtual ~FatalException();

            /* �G���[�v�����擾 */
            virtual char const* what() const noexcept override;

        private:
            /* �G���[���b�Z�[�W���� */
            const std::string GenerateErrorMessage();

        private:
            /* �G���[���b�Z�[�W */
            std::string m_ErrorMessage;
        };
    }
}

/* �v���I��O���o�}�N���֐� */
#define THROW_FATAL_EXCEPTION(message) \
    throw util::exception::FatalException(message, __FILE__, __FUNCTION__, __LINE__)
