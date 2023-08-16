#include "ExceptionBase.h"

#include <sstream>

namespace util
{
    namespace exception
    {
        /* �R���X�g���N�^ */
        ExceptionBase::ExceptionBase(const std::string& message)
            : m_Message(message)
            , m_FilePath("")
            , m_FunctionName("")
            , m_LineNumber(0)
            , m_ErrorInfo("", "", 0)
            , m_IsErrorInfoExists(false)
        {
            /* Nothing to do */
        }

        /* �R���X�g���N�^ */
        ExceptionBase::ExceptionBase(const std::string& message, const std::string& file, const std::string& func, const int line)
            : m_Message(message)
            , m_FilePath(file)
            , m_FunctionName(func)
            , m_LineNumber(line)
            , m_ErrorInfo(file, func, line)
            , m_IsErrorInfoExists(true)
        {
            /* Nothing to do */
        }

        /* �f�X�g���N�^ */
        ExceptionBase::~ExceptionBase()
        {
            /* Nothing to do */
        }

        /* �t�@�C���p�X���擾 */
        const std::string& ExceptionBase::GetFilePath()
        {
            return this->m_FilePath;
        }

        /* �֐������擾 */
        const std::string& ExceptionBase::GetFunctionName()
        {
            return this->m_FunctionName;
        }

        /* �t�@�C���s�ԍ����擾 */
        int ExceptionBase::GetLineNumber()
        {
            return this->m_LineNumber;
        }

        /* �G���[�����擾 */
        const util::exception::ErrorInfo& ExceptionBase::GetErrorInfo()
        {
            return this->m_ErrorInfo;
        }

        /* �G���[�v�����擾 */
        char const* ExceptionBase::what() const noexcept
        {
            /* �G���[��񂪑��݂���ꍇ */
            if (this->m_IsErrorInfoExists == true)
            {
                std::stringstream ss;

                /* �G���[���b�Z�[�W�ɁA�G���[�����ӏ�(�֐����A�t�@�C���p�X�A�t�@�C���s��)��t�� */
                ss << this->m_Message << " @ " << this->m_FunctionName << "[" << this->m_FilePath << ": L." << this->m_LineNumber << "]";

                std::string message = ss.str();

                return message.c_str();
            }
            /* �G���[��񂪑��݂��Ȃ��ꍇ */
            else
            {
                /* �G���[���b�Z�[�W�̂ݏo�� */
                return this->m_Message.c_str();
            }
        }
    }
}
