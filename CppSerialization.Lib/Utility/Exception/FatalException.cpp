#include "FatalException.h"
#include "StackTracer.h"
#include "StringFormat.h"

#include <sstream>

namespace util
{
    namespace exception
    {
        /* �R���X�g���N�^ */
        FatalException::FatalException(const std::string& message)
            : ExceptionBase(message)
            , m_ErrorMessage("")
        {
            /* �G���[���b�Z�[�W���� */
            this->m_ErrorMessage = this->GenerateErrorMessage();
        }

        /* �R���X�g���N�^ */
        FatalException::FatalException(const std::string& message, const std::string& file, const std::string& func, const int line)
            : ExceptionBase(message, file, func, line)
            , m_ErrorMessage("")
        {
            /* �G���[���b�Z�[�W���� */
            this->m_ErrorMessage = this->GenerateErrorMessage();
        }

        /* �f�X�g���N�^ */
        FatalException::~FatalException()
        {
            /* Nothing to do */
        }

        /* �G���[�v�����擾 */
        char const* FatalException::what() const noexcept
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
        const std::string FatalException::GenerateErrorMessage()
        {
            std::stringstream ss;

            /* �G���[��񂪂���ꍇ�́A�G���[���t�����b�Z�[�W�𐶐� */
            if (this->m_IsErrorInfoExists == true)
            {
                ss << util::string::Format("[Fatal Error] %s @ %s[%s:L.%d]", this->m_Message, this->m_FunctionName, this->m_FilePath, this->m_LineNumber);
            }
            else
            {
                ss << util::string::Format("[Fatal Error] %s", this->m_Message);
            }
            ss << std::endl;

            /* �X�^�b�N�g���[�X���_���v */
            util::exception::StackTracer::DumpStackTrace(ss);
            ss << std::endl;

            return ss.str();
        }
    }
}
