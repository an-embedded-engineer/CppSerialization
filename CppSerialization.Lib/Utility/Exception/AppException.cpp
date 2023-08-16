#include "AppException.h"
#include "StackTracer.h"
#include "StringFormat.h"

#include <sstream>
#include <iomanip>
#include <iostream>

namespace util
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
            /* �X�^�b�N�g���[�X�����擾 */
            util::exception::StackTrace stack_trace = util::exception::StackTracer::GetStackTrace();

            std::stringstream ss;

            /* �G���[��񂪂���ꍇ�́A�G���[���t�����b�Z�[�W�𐶐� */
            if (this->m_IsErrorInfoExists == true)
            {
                ss << util::string::Format("[Application Error] %s @ %s[%s:L.%d]", this->m_Message, this->m_FunctionName, this->m_FilePath, this->m_LineNumber);
            }
            else
            {
                ss << util::string::Format("[Application Error] %s", this->m_Message);
            }
            ss << std::endl;

            /* �X�^�b�N�g���[�X���_���v */
            ss << "[Stack Traces] : " << std::endl;
            for (size_t i = 0; i < stack_trace.traces.size(); i++)
            {
                if (i != 0)
                {
                    ss << std::endl;
                }

                ss << "  ";
                ss << std::setw(16) << std::setfill('0') << std::hex << (uint64_t)stack_trace.traces[i];
                ss << " | ";
                if (i < stack_trace.symbols.size())
                {
                    ss << stack_trace.symbols[i];
                }
                else
                {
                    ss << "<Unknown Symbol>";
                }
            }
            ss << std::endl;

            return ss.str();
        }
    }
}
