#pragma once
#include <string>

namespace util
{
    namespace exception
    {
        /* エラー情報 */
        struct ErrorInfo
        {
            /* ファイルパス */
            std::string file_path;

            /* 関数名 */
            std::string function_name;

            /* ファイル行番号 */
            int line_number;

            /* コンストラクタ */
            ErrorInfo(const std::string& file, const std::string& func, const int line)
                : file_path(file)
                , function_name(func)
                , line_number(line)
            {
            }
        };
    }
}
