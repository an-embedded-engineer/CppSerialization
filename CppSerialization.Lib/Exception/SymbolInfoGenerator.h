#pragma once
#include "SymbolInfo.h"

#include <string>

namespace cpp_lib
{
    namespace exception
    {
        /* シンボル情報生成クラス */
        class SymbolInfoGenerator
        {
        public:
            /* シンボル情報テキスト生成 */
            static std::string GenerateSymbolInfoText(const std::string& raw_symbol_info);

        private:
            /* シンボル情報生成 */
            static cpp_lib::exception::SymbolInfo GenerateSymbolInfo(const std::string& raw_symbol_info);
        };
    }
}
