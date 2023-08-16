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
    /* �f�}���O���֐��X�^�u */
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
        /* �V���{�����e�L�X�g���� */
        std::string SymbolInfoGenerator::GenerateSymbolInfoText(const std::string& raw_symbol_info)
        {
            /* �V���{�������擾 */
            const util::exception::SymbolInfo symbol_info = SymbolInfoGenerator::GenerateSymbolInfo(raw_symbol_info);

            /* �V���{�����e�L�X�g�������� */
            std::string symbol_info_text = "";

            /* �V���{����񂪗L�� */
            if (symbol_info.is_valid == true)
            {
                /* �}���O�����ꂽ�V���{�������擾 */
                std::string mangled_symbol_name = symbol_info.mangled_symbol_name;

                /* �}���O�����ꂽ�V���{�����𔻒� */
                if (mangled_symbol_name[0] == '_')
                {
                    /* �f�}���O�����ꂽ�V���{�������擾 */
                    int status = 0;
                    char* demangled_symbol_name = abi::__cxa_demangle(mangled_symbol_name.c_str(), nullptr, nullptr, &status);

                    /* �f�}���O�����ꂽ�V���{�����̎擾����(null�łȂ���)�𔻒� */
                    if (demangled_symbol_name != nullptr)
                    {
                        /* �f�}���O���ɐ���������f�}���O�����ꂽ�V���{�������֐����ɃZ�b�g�A���s������}���O�����ꂽ�V���{�������g�p */
                        std::string function_name = (status == 0) ? demangled_symbol_name : mangled_symbol_name;

                        /* �f�}���O�����ꂽ�V���{�����̃�������� */
                        free(demangled_symbol_name);

                        /* �V���{�����e�L�X�g���Z�b�g */
                        symbol_info_text = util::string::Format("%s %s + %s", symbol_info.object_name, function_name, symbol_info.offset);
                    }
                    else
                    {
                        /* �V���{�����e�L�X�g���Z�b�g */
                        symbol_info_text = util::string::Format("%s %s + %s", symbol_info.object_name, mangled_symbol_name, symbol_info.offset);
                    }
                }
                else
                {
                    /* �V���{�����e�L�X�g���Z�b�g */
                    symbol_info_text = util::string::Format("%s %s + %s", symbol_info.object_name, mangled_symbol_name, symbol_info.offset);
                }
            }
            else
            {
                /* �V���{�����e�L�X�g���Z�b�g */
                symbol_info_text = raw_symbol_info;
            }

            return symbol_info_text;
        }

        /* �V���{����񐶐� */
        util::exception::SymbolInfo SymbolInfoGenerator::GenerateSymbolInfo(const std::string& raw_symbol_info)
        {
#if PLATFORM_TYPE == PLATFORM_MAC || PLATFORM_TYPE == PLATFORM_LINUX
            /* �V���{�����p�^�[�� �F <Depth> <ObjectName> <Address> <MangledSymbolName> + <Offset> */
            std::regex pattern("^(\\d+)\\s+([\\w.\\?]+)\\s+(0x[0-9A-Fa-f]+)\\s+(\\w+)\\s+\\+\\s+(\\d+)$");
            /* �}�b�`�I�u�W�F�N�g������ */
            std::smatch sm;

            /* �V���{����񐶐� */
            util::exception::SymbolInfo symbol_info;

            /* �V���{�����p�^�[���Ƀ}�b�` */
            if (std::regex_match(raw_symbol_info, sm, pattern))
            {
                /* �L���ȃV���{����񐶐� */
                symbol_info.object_name = sm[2].str();
                symbol_info.address = sm[3].str();
                symbol_info.mangled_symbol_name = sm[4].str();
                symbol_info.offset = sm[5].str();
                symbol_info.is_valid = true;
            }
            else
            {
                /* �����ȃV���{����񐶐� */
                symbol_info.object_name = "";
                symbol_info.address = "";
                symbol_info.mangled_symbol_name = "";
                symbol_info.offset = "";
                symbol_info.is_valid = false;
            }

            return symbol_info;
#else
            /* �����ȃV���{�����𐶐� */
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
