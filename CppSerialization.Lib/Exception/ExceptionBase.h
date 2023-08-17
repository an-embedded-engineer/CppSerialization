#pragma once
#include "ErrorInfo.h"

#include <string>
#include <exception>

namespace cpp_lib
{
    namespace exception
    {
        /* 例外基底クラス */
        class ExceptionBase : public std::exception
        {
        public:
            /* コンストラクタ */
            ExceptionBase(const std::string& message);

            /* コンストラクタ */
            ExceptionBase(const std::string& message, const std::string& file, const std::string& func, const int line);

            /* デストラクタ */
            virtual ~ExceptionBase();

            /* ファイルパスを取得 */
            const std::string& GetFilePath();

            /* 関数名を取得 */
            const std::string& GetFunctionName();

            /* ファイル行番号を取得 */
            int GetLineNumber();

            /* エラー情報を取得 */
            const cpp_lib::exception::ErrorInfo& GetErrorInfo();

            /* エラー要因を取得 */
            virtual char const* what() const noexcept override;

        private:
            std::string GenerateFormattedMessage();

        protected:
            /* フォーマット済みエラーメッセージ */
            std::string m_FormattedMessage;

            /* エラーメッセージ */
            std::string m_Message;

            /* ファイルパス */
            std::string m_FilePath;

            /* 関数名 */
            std::string m_FunctionName;

            /* ファイル行番号 */
            int m_LineNumber;

            /* エラー情報 */
            cpp_lib::exception::ErrorInfo m_ErrorInfo;

            /* エラー情報有無 */
            bool m_IsErrorInfoExists;
        };
    }
}
