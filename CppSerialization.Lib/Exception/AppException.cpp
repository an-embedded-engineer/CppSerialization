#include "AppException.h"
#include "StackTracer.h"
#include "StringFormat.h"

#include <sstream>

namespace cpp_lib
{
    namespace exception
    {
        /* �R���X�g���N�^ */
        AppException::AppException(const std::string& message)
            : ExceptionBase(message)
            , m_ErrorMessage("")
        {
            /* �G���[���b�Z�[�W���� */
            this->m_ErrorMessage = this->GenerateErrorMessage();
        }

        /* �R���X�g���N�^ */
        AppException::AppException(const std::string& message, const std::string& file, const std::string& func, const int line)
            : ExceptionBase(message, file, func, line)
            , m_ErrorMessage("")
        {
            /* �G���[���b�Z�[�W���� */
            this->m_ErrorMessage = this->GenerateErrorMessage();
        }

        /* �f�X�g���N�^ */
        AppException::~AppException()
        {
            /* Nothing to do */
        }

        /* �G���[�v�����擾 */
        char const* AppException::what() const noexcept
        {
            /* �G���[��񂪂���ꍇ�́A�G���[���t�����b�Z�[�W���o�� */
            if (this->m_IsErrorInfoExists == true)
            {
                return this->m_ErrorMessage.c_str();
            }
            else
            {
                return this->m_Message.c_str();
            }
        }

        /* �G���[���b�Z�[�W���� */
        const std::string AppException::GenerateErrorMessage()
        {
            std::stringstream ss;

            /* �G���[��񂪂���ꍇ�́A�G���[���t�����b�Z�[�W�𐶐� */
            if (this->m_IsErrorInfoExists == true)
            {
                ss << cpp_lib::string::Format("[Application Error] %s @ %s[%s:L.%d]", this->m_Message, this->m_FunctionName, this->m_FilePath, this->m_LineNumber);
            }
            else
            {
                ss << cpp_lib::string::Format("[Application Error] %s", this->m_Message);
            }
            ss << std::endl;

            /* �X�^�b�N�g���[�X���_���v */
            cpp_lib::exception::StackTracer::DumpStackTrace(ss);
            ss << std::endl;

            return ss.str();
        }
    }
}
