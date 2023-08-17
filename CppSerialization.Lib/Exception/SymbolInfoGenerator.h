#pragma once
#include "SymbolInfo.h"

#include <string>

namespace cpp_lib
{
    namespace exception
    {
        /* �V���{����񐶐��N���X */
        class SymbolInfoGenerator
        {
        public:
            /* �V���{�����e�L�X�g���� */
            static std::string GenerateSymbolInfoText(const std::string& raw_symbol_info);

        private:
            /* �V���{����񐶐� */
            static cpp_lib::exception::SymbolInfo GenerateSymbolInfo(const std::string& raw_symbol_info);
        };
    }
}
