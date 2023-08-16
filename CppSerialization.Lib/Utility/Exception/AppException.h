#pragma once
#include "ExceptionBase.h"

#include <string>

namespace util
{
    namespace exception
    {
        /* Application Exceptionクラス宣言 */
        class AppException : public util::exception::ExceptionBase
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

/* Application Exceptionのthrow */
#define THROW_APP_EXCEPTION(message) \
    throw util::exception::AppException(message, __FILE__, __FUNCTION__, __LINE__)
