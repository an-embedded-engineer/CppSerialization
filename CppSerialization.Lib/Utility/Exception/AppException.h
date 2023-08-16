#pragma once
#include "ExceptionBase.h"

#include <string>

namespace util
{
    namespace exception
    {
        /* Application Exception�N���X�錾 */
        class AppException : public util::exception::ExceptionBase
        {
        public:
            /* �R���X�g���N�^ */
            AppException(const std::string& message);

            /* �R���X�g���N�^ */
            AppException(const std::string& message, const std::string& file, const std::string& func, const int line);

            /* �f�X�g���N�^ */
            virtual ~AppException();

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

/* Application Exception��throw */
#define THROW_APP_EXCEPTION(message) \
    throw util::exception::AppException(message, __FILE__, __FUNCTION__, __LINE__)
