#include "ExceptionBase.h"

#include <sstream>

namespace cpp_lib
{
    namespace exception
    {
        /* �R���X�g���N�^ */
        ExceptionBase::ExceptionBase(const std::string& message)
            : m_FormattedMessage("")
            , m_Message(message)
            , m_FilePath("")
            , m_FunctionName("")
            , m_LineNumber(0)
            , m_ErrorInfo("", "", 0)
            , m_IsErrorInfoExists(false)
        {
            /* �t�H�[�}�b�g�ς݃��b�Z�[�W���� */
            this->m_FormattedMessage = this->GenerateFormattedMessage();
        }

        /* �R���X�g���N�^ */
        ExceptionBase::ExceptionBase(const std::string& message, const std::string& file, const std::string& func, const int line)
            : m_FormattedMessage("")
            , m_Message(message)
            , m_FilePath(file)
            , m_FunctionName(func)
            , m_LineNumber(line)
            , m_ErrorInfo(file, func, line)
            , m_IsErrorInfoExists(true)
        {
            /* �t�H�[�}�b�g�ς݃��b�Z�[�W���� */
            this->m_FormattedMessage = this->GenerateFormattedMessage();
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
        const cpp_lib::exception::ErrorInfo& ExceptionBase::GetErrorInfo()
        {
            return this->m_ErrorInfo;
        }

        /* �G���[�v�����擾 */
        char const* ExceptionBase::what() const noexcept
        {
            return this->m_FormattedMessage.c_str();
        }

        std::string ExceptionBase::GenerateFormattedMessage()
        {
            /* �G���[��񂪑��݂���ꍇ */
            if (this->m_IsErrorInfoExists == true)
            {
                std::ostringstream ss;

                /* �G���[���b�Z�[�W�ɁA�G���[�����ӏ�(�֐����A�t�@�C���p�X�A�t�@�C���s��)��t�� */
                ss << this->m_Message << " @ " << this->m_FunctionName << "[" << this->m_FilePath << ": L." << this->m_LineNumber << "]";

                return ss.str();
            }
            /* �G���[��񂪑��݂��Ȃ��ꍇ */
            else
            {
                /* �G���[���b�Z�[�W�̂ݏo�� */
                return this->m_Message;
            }
        }
    }
}
