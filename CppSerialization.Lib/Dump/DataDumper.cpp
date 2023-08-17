#include "DataDumper.h"

namespace cpp_lib
{
    namespace dump
    {
        /* コンテナ型の1行に出力する要素数 */
        const int DataDumper::ContainerValuesSingleLineNum = 30;

        /* インデント文字列生成 */
        std::string DataDumper::GetIndent(const size_t depth)
        {
            size_t count = depth * 2;

            std::string indent(count, ' ');

            return indent;
        }
    }
}
