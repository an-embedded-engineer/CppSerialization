#pragma once
#include <string>

namespace util
{
    namespace exception
    {
        /* シンボル情報 */
        struct SymbolInfo
        {
            /* シンボル情報有効フラグ */
            bool is_valid;
            /* オブジェクト名 */
            std::string object_name;
            /* アドレス */
            std::string address;
            /* マングルされたシンボル名 */
            std::string mangled_symbol_name;
            /* オフセット */
            std::string offset;

            /* コンストラクタ */
            SymbolInfo()
                : is_valid(false)
                , object_name("")
                , address("")
                , mangled_symbol_name("")
                , offset("")
            {
                /* Nothing to do */
            }
        };
    }
}
