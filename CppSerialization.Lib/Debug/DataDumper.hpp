#pragma once
#include "DataDumper.h"
#include "DomainModelDataTypes.h"

namespace debug
{
    /* Explicit Instantiations */
    template void DataDumper::Dump<dm::StrucMessage1>(const dm::StrucMessage1& data, const size_t depth, std::stringstream& ss);
    template void DataDumper::Dump<dm::StrucMessage2>(const dm::StrucMessage2& data, const size_t depth, std::stringstream& ss);
    template void DataDumper::Dump<dm::StrucMessage3>(const dm::StrucMessage3& data, const size_t depth, std::stringstream& ss);
}
