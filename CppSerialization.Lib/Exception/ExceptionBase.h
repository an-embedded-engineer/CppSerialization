#pragma once
#include "ErrorInfo.h"

#include <string>
#include <exception>

namespace cpp_lib
{
    namespace exception
    {
        /* ��O���N���X */
        class ExceptionBase : public std::exception
        {
        public:
            /* �R���X�g���N�^ */
            ExceptionBase(const std::string& message);

            /* �R���X�g���N�^ */
            ExceptionBase(const std::string& message, const std::string& file, const std::string& func, const int line);

            /* �f�X�g���N�^ */
            virtual ~ExceptionBase();

            /* �t�@�C���p�X���擾 */
            const std::string& GetFilePath();

            /* �֐������擾 */
            const std::string& GetFunctionName();

            /* �t�@�C���s�ԍ����擾 */
            int GetLineNumber();

            /* �G���[�����擾 */
            const cpp_lib::exception::ErrorInfo& GetErrorInfo();

            /* �G���[�v�����擾 */
            virtual char const* what() const noexcept override;

        private:
            std::string GenerateFormattedMessage();

        protected:
            /* �t�H�[�}�b�g�ς݃G���[���b�Z�[�W */
            std::string m_FormattedMessage;

            /* �G���[���b�Z�[�W */
            std::string m_Message;

            /* �t�@�C���p�X */
            std::string m_FilePath;

            /* �֐��� */
            std::string m_FunctionName;

            /* �t�@�C���s�ԍ� */
            int m_LineNumber;

            /* �G���[��� */
            cpp_lib::exception::ErrorInfo m_ErrorInfo;

            /* �G���[���L�� */
            bool m_IsErrorInfoExists;
        };
    }
}
