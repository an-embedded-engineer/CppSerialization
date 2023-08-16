#pragma once
#include "SymbolInfo.h"

#include <string>

namespace util
{
    namespace exception
    {
        /* Symbol Info Generatorクラス宣言 */
        class SymbolInfoGenerator
        {
        public:
            /* シンボル情報テキスト生成 */
            static std::string GenerateSymbolInfoText(const std::string& raw_symbol_info);

        private:
            /* シンボル情報生成 */
            static util::exception::SymbolInfo GenerateSymbolInfo(const std::string& raw_symbol_info);
        };
    }
}
