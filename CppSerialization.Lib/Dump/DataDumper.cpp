#include "DataDumper.h"

namespace cpp_lib
{
    namespace dump
    {
        /* �R���e�i�^��1�s�ɏo�͂���v�f�� */
        const int DataDumper::ContainerValuesSingleLineNum = 30;

        /* �C���f���g�����񐶐� */
        std::string DataDumper::GetIndent(const size_t depth)
        {
            size_t count = depth * 2;

            std::string indent(count, ' ');

            return indent;
        }
    }
}
