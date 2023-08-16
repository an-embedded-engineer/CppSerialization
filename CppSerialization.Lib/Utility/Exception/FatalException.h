#pragma once
#include "ExceptionBase.h"

#include <string>

namespace util
{
    namespace exception
    {
        /* Fatal Exceptionクラス宣言 */
        class FatalException : public util::exception::ExceptionBase
        {
        public:
            /* コンストラクタ */
            FatalException(const std::string& message);

            /* コンストラクタ */
            FatalException(const std::string& message, const std::string& file, const std::string& func, const int line);

            /* デストラクタ */
            virtual ~FatalException();

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

/* Fatal Exceptionのthrow */
#define THROW_FATAL_EXCEPTION(message) \
    throw util::exception::FatalException(message, __FILE__, __FUNCTION__, __LINE__)
