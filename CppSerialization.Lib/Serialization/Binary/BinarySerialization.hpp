#pragma once
#include "BinarySerialization.h"
#include "DomainModelDataTypes.h"

namespace serialization
{
    /* Explicit Instantiation */
    /* dm::StrucMessage1 */
    template void BinarySerialization::Calculate<dm::StrucMessage1>(const dm::StrucMessage1& in_data, size_t& out_size, typename std::enable_if<std::is_class<dm::StrucMessage1>::value>::type*);
    template void BinarySerialization::Serialize<dm::StrucMessage1>(const dm::StrucMessage1& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<dm::StrucMessage1>::value>::type*);
    template void BinarySerialization::Deserialize<dm::StrucMessage1>(const serialization::Archive& in_archive, size_t& offset, dm::StrucMessage1& out_data, typename std::enable_if<std::is_class<dm::StrucMessage1>::value>::type*);

    /* dm::StrucMessage2 */
    template void BinarySerialization::Calculate<dm::StrucMessage2>(const dm::StrucMessage2& in_data, size_t& out_size, typename std::enable_if<std::is_class<dm::StrucMessage2>::value>::type*);
    template void BinarySerialization::Serialize<dm::StrucMessage2>(const dm::StrucMessage2& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<dm::StrucMessage2>::value>::type*);
    template void BinarySerialization::Deserialize<dm::StrucMessage2>(const serialization::Archive& in_archive, size_t& offset, dm::StrucMessage2& out_data, typename std::enable_if<std::is_class<dm::StrucMessage2>::value>::type*);

    /* dm::StrucMessage3 */
    template void BinarySerialization::Calculate<dm::StrucMessage3>(const dm::StrucMessage3& in_data, size_t& out_size, typename std::enable_if<std::is_class<dm::StrucMessage3>::value>::type*);
    template void BinarySerialization::Serialize<dm::StrucMessage3>(const dm::StrucMessage3& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<dm::StrucMessage3>::value>::type*);
    template void BinarySerialization::Deserialize<dm::StrucMessage3>(const serialization::Archive& in_archive, size_t& offset, dm::StrucMessage3& out_data, typename std::enable_if<std::is_class<dm::StrucMessage3>::value>::type*);
}
