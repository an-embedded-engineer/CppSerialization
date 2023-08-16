#include "DataDumper.h"
#include "DataDumper.hpp"
#include "DataTypeTraits.h"

namespace debug
{
    /* �R���e�i�^��1�s�ɏo�͂���v�f�� */
    const int DataDumper::ContainerValuesSingleLineNum = 30;

    /* Dump Class/Structure Data to String Stream with Indent Depth */
    template<typename T, util::type_traits::concept_t<std::is_class<T>::value>>
    void DataDumper::Dump(const T& data, const size_t depth, std::stringstream& ss)
    {
        auto tuple = dm::DataTypeTraits<T>::GetNamedMembersAsTuple(data);

        DataDumper::DumpTuple(depth, ss, tuple);
    }

    /* Get Indent String */
    std::string DataDumper::GetIndent(const size_t depth)
    {
        size_t count = depth * 2;

        std::string indent(count, ' ');

        return indent;
    }
}
