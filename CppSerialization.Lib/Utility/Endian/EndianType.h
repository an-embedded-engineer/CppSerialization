#pragma once
#include <string>
#include <stdexcept>

namespace util
{
    namespace endian
    {
        /* エンディアンタイプ */
        enum class EndianType
        {
            Big,                /* ビッグエンディアン */
            Little,             /* リトルエンディアン */
            Network = Big,      /* ネットワークバイトオーダー = ビッグエンディアン */
        };

        /* エンディアンタイプを文字列に変換 */
        static std::string ToString(EndianType type)
        {
            switch (type)
            {
            case util::endian::EndianType::Big:
                return "Big";
            case util::endian::EndianType::Little:
                return "Little";
            default:
                throw std::invalid_argument("Invalid Endian Type : " + std::to_string(static_cast<int>(type)));
            }
        }
    }
}
