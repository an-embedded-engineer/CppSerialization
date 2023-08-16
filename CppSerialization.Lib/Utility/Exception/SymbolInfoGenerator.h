#pragma once
#include "SymbolInfo.h"

#include <string>

namespace util
{
    namespace exception
    {
        /* Symbol Info Generator�N���X�錾 */
        class SymbolInfoGenerator
        {
        public:
            /* �V���{�����e�L�X�g���� */
            static std::string GenerateSymbolInfoText(const std::string& raw_symbol_info);

        private:
            /* �V���{����񐶐� */
            static util::exception::SymbolInfo GenerateSymbolInfo(const std::string& raw_symbol_info);
        };
    }
}
