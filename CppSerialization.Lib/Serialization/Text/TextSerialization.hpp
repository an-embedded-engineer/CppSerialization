#pragma once
#include "TextSerialization.h"
#include "DomainModelDataTypes.h"

namespace serialization
{
    /* Explicit Instantiation */
    /* dm::StrucMessage1 */
    template void TextSerialization::Serialize<dm::StrucMessage1>(const dm::StrucMessage1& in_data, Node& out_node, typename std::enable_if<std::is_class<dm::StrucMessage1>::value>::type*);
    template void TextSerialization::Deserialize<dm::StrucMessage1>(const Node& in_node, dm::StrucMessage1& out_data, typename std::enable_if<std::is_class<dm::StrucMessage1>::value>::type*);

    /* dm::StrucMessage2 */
    template void TextSerialization::Serialize<dm::StrucMessage2>(const dm::StrucMessage2& in_data, Node& out_node, typename std::enable_if<std::is_class<dm::StrucMessage2>::value>::type*);
    template void TextSerialization::Deserialize<dm::StrucMessage2>(const Node& in_node, dm::StrucMessage2& out_data, typename std::enable_if<std::is_class<dm::StrucMessage2>::value>::type*);

    /* dm::StrucMessage3 */
    template void TextSerialization::Serialize<dm::StrucMessage3>(const dm::StrucMessage3& in_data, Node& out_node, typename std::enable_if<std::is_class<dm::StrucMessage3>::value>::type*);
    template void TextSerialization::Deserialize<dm::StrucMessage3>(const Node& in_node, dm::StrucMessage3& out_data, typename std::enable_if<std::is_class<dm::StrucMessage3>::value>::type*);
}
