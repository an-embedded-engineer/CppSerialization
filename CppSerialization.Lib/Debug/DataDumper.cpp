#include "DataDumper.h"
#include "DataDumper.hpp"
#include "DataTypeTraits.h"

namespace debug
{
    /* コンテナ型の1行に出力する要素数 */
    const int DataDumper::ContainerValuesSingleLineNum = 30;

    /* クラス/構造体(class/struct)型ダンプ(インデント付き) */
    template<typename T, util::type_traits::concept_t<std::is_class<T>::value>>
    void DataDumper::Dump(const T& data, const size_t depth, std::stringstream& ss)
    {
        /* メンバの名前付きタプル取得 */
        auto tuple = dm::DataTypeTraits<T>::GetNamedMembersAsTuple(data);

        /* メンバの名前付きタプルをダンプ */
        DataDumper::DumpTuple(depth, ss, tuple);
    }

    /* インデント文字列生成 */
    std::string DataDumper::GetIndent(const size_t depth)
    {
        size_t count = depth * 2;

        std::string indent(count, ' ');

        return indent;
    }
}
