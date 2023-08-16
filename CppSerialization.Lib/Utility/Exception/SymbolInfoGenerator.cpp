#include "SymbolInfoGenerator.h"
#include "PlatformConfig.h"
#include "StringFormat.h"

#include <regex>
#include <typeinfo>

#if ((PLATFORM_TYPE_OVERRIDE_ENABLED == 0) && (PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX))
#include <cxxabi.h>
#else
namespace abi
{
    /* デマングル関数スタブ */
    inline char* __cxa_demangle(const char* mangled_name, char* output_buffer, size_t* length, int* status)
    {
        output_buffer = nullptr;
        length = nullptr;
        *status = 0;
        return nullptr;
    }
}
#endif

namespace util
{
    namespace exception
    {
        /* シンボル情報テキスト生成 */
        std::string SymbolInfoGenerator::GenerateSymbolInfoText(const std::string& raw_symbol_info)
        {
            /* シンボル情報を取得 */
            const util::exception::SymbolInfo symbol_info = SymbolInfoGenerator::GenerateSymbolInfo(raw_symbol_info);

            /* シンボル情報テキストを初期化 */
            std::string symbol_info_text = "";

            /* シンボル情報が有効 */
            if (symbol_info.is_valid == true)
            {
                /* マングルされたシンボル名を取得 */
                std::string mangled_symbol_name = symbol_info.mangled_symbol_name;

                /* マングルされたシンボル名を判定 */
                if (mangled_symbol_name[0] == '_')
                {
                    /* デマングルされたシンボル名を取得 */
                    int status = 0;
                    char* demangled_symbol_name = abi::__cxa_demangle(mangled_symbol_name.c_str(), nullptr, nullptr, &status);

                    /* デマングルされたシンボル名の取得成功(nullでないか)を判定 */
                    if (demangled_symbol_name != nullptr)
                    {
                        /* デマングルに成功したらデマングルされたシンボル名を関数名にセット、失敗したらマングルされたシンボル名を使用 */
                        std::string function_name = (status == 0) ? demangled_symbol_name : mangled_symbol_name;

                        /* デマングルされたシンボル名のメモリ解放 */
                        free(demangled_symbol_name);

                        /* シンボル情報テキストをセット */
                        symbol_info_text = util::string::Format("%s %s + %s", symbol_info.object_name, function_name, symbol_info.offset);
                    }
                    else
                    {
                        /* シンボル情報テキストをセット */
                        symbol_info_text = util::string::Format("%s %s + %s", symbol_info.object_name, mangled_symbol_name, symbol_info.offset);
                    }
                }
                else
                {
                    /* シンボル情報テキストをセット */
                    symbol_info_text = util::string::Format("%s %s + %s", symbol_info.object_name, mangled_symbol_name, symbol_info.offset);
                }
            }
            else
            {
                /* シンボル情報テキストをセット */
                symbol_info_text = raw_symbol_info;
            }

            return symbol_info_text;
        }

        /* シンボル情報生成 */
        util::exception::SymbolInfo SymbolInfoGenerator::GenerateSymbolInfo(const std::string& raw_symbol_info)
        {
#if PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* シンボル情報パターン ： <Depth> <ObjectName> <Address> <MangledSymbolName> + <Offset> */
            std::regex pattern("^(\\d+)\\s+([\\w.\\?]+)\\s+(0x[0-9A-Fa-f]+)\\s+(\\w+)\\s+\\+\\s+(\\d+)$");
            /* マッチオブジェクト初期化 */
            std::smatch sm;

            /* シンボル情報生成 */
            util::exception::SymbolInfo symbol_info;

            /* シンボル情報パターンにマッチ */
            if (std::regex_match(raw_symbol_info, sm, pattern))
            {
                /* 有効なシンボル情報生成 */
                symbol_info.object_name = sm[2].str();
                symbol_info.address = sm[3].str();
                symbol_info.mangled_symbol_name = sm[4].str();
                symbol_info.offset = sm[5].str();
                symbol_info.is_valid = true;
            }
            else
            {
                /* 無効なシンボル情報生成 */
                symbol_info.object_name = "";
                symbol_info.address = "";
                symbol_info.mangled_symbol_name = "";
                symbol_info.offset = "";
                symbol_info.is_valid = false;
            }

            return symbol_info;
#else
            /* 無効なシンボル情報を生成 */
            util::exception::SymbolInfo symbol_info;
            symbol_info.object_name = "";
            symbol_info.address = "";
            symbol_info.mangled_symbol_name = "";
            symbol_info.offset = "";
            symbol_info.is_valid = false;

            return symbol_info;
#endif
        }
    }
}
