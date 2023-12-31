#pragma once
#include "ExceptionBase.h"

#include <string>

namespace cpp_lib
{
    namespace exception
    {
        /* アプリケーション例外クラス */
        class AppException : public cpp_lib::exception::ExceptionBase
        {
        public:
            /* コンストラクタ */
            AppException(const std::string& message);

            /* コンストラクタ */
            AppException(const std::string& message, const std::string& file, const std::string& func, const int line);

            /* デストラクタ */
            virtual ~AppException();

            /* エラー要因を取得 */
            virtual char const* what() const noexcept override;

        private:
            /* エラーメッセージ生成 */
            const std::string GenerateErrorMessage();

        private:
            /* エラーメッセージ */
            std::string m_ErrorMessage;
        };
    }
}

/* アプリケーション例外送出マクロ関数 */
#define THROW_APP_EXCEPTION(message) \
    throw cpp_lib::exception::AppException(message, __FILE__, __FUNCTION__, __LINE__)
