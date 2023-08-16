#pragma once
#include <string>

namespace util
{
    namespace exception
    {
        /* �G���[��� */
        struct ErrorInfo
        {
            /* �t�@�C���p�X */
            std::string file_path;

            /* �֐��� */
            std::string function_name;

            /* �t�@�C���s�ԍ� */
            int line_number;

            /* �R���X�g���N�^ */
            ErrorInfo(const std::string& file, const std::string& func, const int line)
                : file_path(file)
                , function_name(func)
                , line_number(line)
            {
            }
        };
    }
}
