#include "TextSerialization.h"

#include <iomanip>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#define TEXT_SERIALIZE_MODE_XML     (0)
#define TEXT_SERIALIZE_MODE_JSON    (1)

#define TEXT_SERIALIZE_MODE         (TEXT_SERIALIZE_MODE_XML)

namespace cpp_lib
{
    namespace serialization
    {
        /* シングルトンインスタンス取得 */
        TextSerialization& TextSerialization::GetInstance()
        {
            static TextSerialization instance;
            return instance;
        }


        /* 論理型(bool)データサイズ算出 */
        void TextSerialization::Serialize(const bool_t& in_data, Node& out_node)
        {
            /* ツリーノードに値を追加 */
            out_node.put_value(in_data);
        }

        /* 論理型(bool)デシリアライズ */
        void TextSerialization::Deserialize(const Node& in_node, bool_t& out_data)
        {
            /* ツリーノードから要素取得 */
            if (auto value = in_node.get_value_optional<bool_t>())
            {
                /* ツリーノード要素から値を取得 */
                out_data = value.get();
            }
            /* 要素取得失敗時は例外創出 */
            else
            {
                THROW_APP_EXCEPTION("Value is nothing");
            }
        }

        /* 文字列型シリアライズ */
        void TextSerialization::Serialize(const string_t& in_data, Node& out_node)
        {
            /* ツリーノードに値を追加 */
            out_node.put_value(in_data);
        }

        /* 文字列型デシリアライズ */
        void TextSerialization::Deserialize(const Node& in_node, string_t& out_data)
        {
            /* ツリーノードから要素取得 */
            if (auto value = in_node.get_value_optional<string_t>())
            {
                /* ツリーノード要素から値を取得 */
                out_data = value.get();
            }
            /* 要素取得失敗時は例外創出 */
            else
            {
                THROW_APP_EXCEPTION("Value is nothing");
            }
        }


        /* シリアライズしたツリーノードをテキストに変換し、アーカイブにセット */
        void TextSerialization::WriteText(const Node& in_root_node, serialization::Archive& out_archive)
        {
            /* 文字列ストリーム */
            std::stringstream ss;

            /* インデントサイズ */
            const int indent = 2;

#if TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_XML
            /* XML書き込み設定(インデント文字、インデントサイズ、エンコーディング) */
            auto setting = boost::property_tree::xml_parser::xml_writer_make_settings<string_t>(' ', indent, boost::property_tree::xml_parser::widen<string_t>("utf-8"));

            /* XMLとして文字列ストリームに書き込み */
            boost::property_tree::write_xml(ss, in_root_node, setting);
#elif TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_JSON
            /* JSONとして文字列ストリームに書き込み */
            boost::property_tree::write_json(ss, in_root_node);
#else
#error Invalid Serialize Mode TEXT_SERIALIZE_MODE
#endif

            /* 文字列に変換 */
            string_t in_str = ss.str();

            /* 文字列長を取得 */
            size_t text_len = in_str.length();

            /* バッファサイズ算出(文字列長 + 終端文字(null文字)サイズ) */
            size_t buffer_size = text_len + 1;

            /* シリアライズ後のデータサイズでアーカイブのデータバッファメモリ確保 */
            out_archive.Reserve(buffer_size);

            /* オフセット初期化 */
            size_t offset = 0;

            /* 指定オフセット位置から文字列データ書き込み */
            out_archive.Write(in_str, offset);
        }

        /* アーカイブをテキストに変換し、ツリーノードに変換 */
        void TextSerialization::ReadText(const serialization::Archive& in_archive, Node& out_root_node)
        {
            /* 文字列ストリーム */
            std::stringstream ss;

            /* アーカイブのデータバッファ(ポインタ)を文字列ストリームに追加 */
            ss << in_archive.GetDataPtr();

#if TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_XML
            /* 文字列ストリームをXMLとしてツリーノードに読み込み */
            boost::property_tree::read_xml(ss, out_root_node);
#elif TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_JSON
            /* 文字列ストリームをJSONとしてツリーノードに読み込み */
            boost::property_tree::read_json(ss, out_root_node);
#else
#error Invalid Serialize Mode TEXT_SERIALIZE_MODE
#endif
        }

        /* 浮動小数データ(32bit)を16進数文字列に変換 */
        void TextSerialization::ToHexString(const float32_t& in_data, string_t& out_data)
        {
            /* 文字列ストリーム */
            std::stringstream ss;

            /* 浮動小数 <=> 整数変換器 */
            cpp_lib::binary::FloatIntConverter<float32_t, uint32_t> converter;

            /* 浮動小数 => 整数変換 */
            uint32_t int_data = converter.ConvertToInt(in_data);

            /* 変換した整数を16進数文字列として文字列ストリームに追加 */
            ss << std::showbase;
            ss << std::setw(4);
            ss << std::hex << int_data;

            /* 文字列に変換 */
            out_data = ss.str();
        }

        /* 浮動小数データ(64bit)を16進数文字列に変換 */
        void TextSerialization::ToHexString(const float64_t& in_data, string_t& out_data)
        {
            /* 文字列ストリーム */
            std::stringstream ss;

            /* 浮動小数 <=> 整数変換器 */
            cpp_lib::binary::FloatIntConverter<float64_t, uint64_t> converter;

            /* 浮動小数 => 整数変換 */
            uint64_t int_data = converter.ConvertToInt(in_data);

            /* 変換した整数を16進数文字列として文字列ストリームに追加 */
            ss << std::showbase;
            ss << std::setw(8);
            ss << std::hex << int_data;

            /* 文字列に変換 */
            out_data = ss.str();
        }

        /* 16進数文字列を浮動小数(32bit)データに変換 */
        void TextSerialization::FromHexString(const string_t& in_data, float32_t& out_data)
        {
            /* 16進数文字列を整数に変換 */
            uint32_t int_data = std::stoul(in_data, nullptr, 16);

            /* 浮動小数 <=> 整数変換器 */
            cpp_lib::binary::FloatIntConverter<float32_t, uint32_t> converter;

            /* 整数 => 浮動小数変換 */
            out_data = converter.ConvertToFloat(int_data);
        }

        /* 16進数文字列を浮動小数(64bit)データに変換 */
        void TextSerialization::FromHexString(const string_t& in_data, float64_t& out_data)
        {
            /* 16進数文字列を整数に変換 */
            uint64_t int_data = std::stoull(in_data, nullptr, 16);

            /* 浮動小数 <=> 整数変換器 */
            cpp_lib::binary::FloatIntConverter<float64_t, uint64_t> converter;

            /* 整数 => 浮動小数変換 */
            out_data = converter.ConvertToFloat(int_data);
        }
    }
}
