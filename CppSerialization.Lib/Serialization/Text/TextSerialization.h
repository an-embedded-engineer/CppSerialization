#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "DataTypeTraits.h"
#include "Archive.h"
#include "FloatIntConverter.h"
#include "AppException.h"
#include "StringFormat.h"

#include <sstream>
#include <iomanip>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#define TEXT_SERIALIZE_MODE_XML     (0)
#define TEXT_SERIALIZE_MODE_JSON    (1)

#define TEXT_SERIALIZE_MODE         (TEXT_SERIALIZE_MODE_JSON)

namespace cpp_lib
{
    namespace serialization
    {
        /* テキスト形式シリアライズクラス */
        class TextSerialization
        {
        public:
            /* ツリーノード型 */
            using Node = boost::property_tree::ptree;

        public:
            /* シングルトンインスタンス取得 */
            static TextSerialization& GetInstance()
            {
                static TextSerialization instance;
                return instance;
            }

        private:
            /* コンストラクタ */
            TextSerialization() = default;

            /* デストラクタ */
            ~TextSerialization() = default;

        public:
            /* コピー&ムーブセマンティクス無効化 */
            TextSerialization(const TextSerialization&) = delete;
            TextSerialization(TextSerialization&&) = delete;
            TextSerialization& operator=(const TextSerialization&) = delete;
            TextSerialization& operator=(TextSerialization&&) = delete;

        public:
            /* 入力データをシリアライズしてアーカイブに変換 */
            template <typename T>
            void Serialize(const T& in_data, const string_t& name, serialization::Archive& out_archive)
            {
                /* ルートノード */
                Node root_node{};

                /* シリアライズ */
                this->Serialize(in_data, name, root_node);

                /* シリアライズしたツリーノードをテキストに変換し、アーカイブにセット */
                this->WriteText(root_node, out_archive);
            }

            /* アーカイブをデシリアライズして出力データに変換 */
            template <typename T>
            void Deserialize(const serialization::Archive& in_archive, const string_t& name, T& out_data)
            {
                /* ルートノード */
                Node root_node{};

                /* アーカイブをテキストに変換し、ツリーノードに変換 */
                this->ReadText(in_archive, root_node);

                /* デシリアライズ */
                this->Deserialize(root_node, name, out_data);
            }

        private:
            /* 整数型シリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_integral<T>::value> = nullptr>
            void Serialize(const T& in_data, Node& out_node)
            {
                /* ツリーノードに値を追加 */
                out_node.put_value(in_data);
            }

            /* 整数型デシリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_integral<T>::value> = nullptr>
            void Deserialize(const Node& in_node, T& out_data)
            {
                /* ツリーノードから要素取得 */
                if (auto value = in_node.get_value_optional<T>())
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


            /* 浮動小数型シリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
            void Serialize(const T& in_data, Node& out_node)
            {
                /* 16進数文字列 */
                string_t in_str{};

                /* 浮動小数データを16進数文字列に変換 */
                this->ToHexString(in_data, in_str);

                /* ツリーノードに16進数文字列に変換した値を追加 */
                out_node.put_value(in_str);
            }

            /* 浮動小数型デシリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
            void Deserialize(const Node& in_node, T& out_data)
            {
                /* 16進数文字列 */
                string_t out_str{};

                /* ツリーノードから要素取得 */
                if (auto value = in_node.get_value_optional<string_t>())
                {
                    /* ツリーノード要素から値を取得 */
                    out_str = value.get();

                    /* 取得した値(16進数文字列)を浮動小数データに変換 */
                    this->FromHexString(out_str, out_data);
                }
                /* 要素取得失敗時は例外創出 */
                else
                {
                    THROW_APP_EXCEPTION("Value is nothing");
                }
            }

            /* 列挙型(enum/enum class)シリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Serialize(const T& in_data, Node& out_node)
            {
                /* 入力データの基底型にキャストしてシリアライズ */
                this->Serialize(cpp_lib::type_traits::underlying_cast(in_data), out_node);
            }

            /* 列挙型(enum/enum class)デシリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Deserialize(const Node& in_node, T& out_data)
            {
                /* 入力データの基底型データ */
                cpp_lib::type_traits::underlying_type_t<T> data{};

                /* 入力データの基底型としてデシリアライズ */
                this->Deserialize(in_node, data);

                /* 入力データの型にキャストしてセット */
                out_data = static_cast<T>(data);
            }

            /* std::array型シリアライズ */
            template <typename T, size_t N>
            void Serialize(const std::array<T, N>& in_data, const string_t& name, Node& out_node)
            {
                /* 名前を指定して子ノードを追加 */
                auto& child_node = out_node.add(name, "");

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素をシリアライズして子ノードに追加 */
                    this->Serialize(item, "item", child_node);
                }
            }

            /* std::array型デシリアライズ */
            template <typename T, size_t N>
            void Deserialize(const Node& in_node, const string_t& name, std::array<T, N>& out_data)
            {
                /* 名前を指定して子ノードを取得 */
                auto& child_node = in_node.get_child(name);

                /* インデックス */
                size_t i = 0;

                /* 子ノードの全要素を走査 */
                for (const auto& item_node_pair : child_node)
                {
                    /* 要素 */
                    T item{};

                    /* 各要素をデシリアライズ */
                    this->Deserialize(item_node_pair.second, item);

                    /* 要素をセット */
                    out_data[i] = item;

                    /* インデックスインクリメント */
                    i++;
                }
            }


            /* std::vector型シリアライズ */
            template <typename T>
            void Serialize(const std::vector<T>& in_data, const string_t& name, Node& out_node)
            {
                /* 名前を指定して子ノードを追加 */
                auto& child_node = out_node.add(name, "");

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素をシリアライズして子ノードに追加 */
                    this->Serialize(item, "item", child_node);
                }
            }

            /* std::vector型デシリアライズ */
            template <typename T>
            void Deserialize(const Node& in_node, const string_t& name, std::vector<T>& out_data)
            {
                /* 名前を指定して子ノードを取得 */
                auto& child_node = in_node.get_child(name);

                /* 出力データクリア */
                out_data.clear();

                /* 子ノードの要素数分メモリを事前確保 */
                out_data.reserve(child_node.size());

                /* 子ノードの全要素を走査 */
                for (const auto& item_node_pair : child_node)
                {
                    /* 要素 */
                    T item{};

                    /* 各要素をデシリアライズ */
                    this->Deserialize(item_node_pair.second, item);

                    /* 要素を追加 */
                    out_data.push_back(item);
                }
            }


            /* std::pair型シリアライズ */
            template <typename T1, typename T2>
            void Serialize(const std::pair<T1, T2>& in_data, Node& out_node)
            {
                /* 1st要素シリアライズ */
                this->Serialize(in_data.first, "first", out_node);

                /* 2nd要素シリアライズ */
                this->Serialize(in_data.second, "second", out_node);
            }

            /* std::pair型デシリアライズ */
            template <typename T1, typename T2>
            void Deserialize(const Node& in_node, std::pair<T1, T2>& out_data)
            {
                /* 1st要素 */
                T1 first{};

                /* 1st要素デシリアライズ */
                this->Deserialize(in_node, "first", first);

                /* 2nd要素 */
                T2 second{};

                /* 2nd要素デシリアライズ */
                this->Deserialize(in_node, "second", second);

                /* std::pairに変換してセット */
                out_data = std::make_pair<T1, T2>(first, second);
            }


            /* std::map型シリアライズ */
            template <typename TKey, typename TValue>
            void Serialize(const std::map<TKey, TValue>& in_data, const string_t& name, Node& out_node)
            {
                /* 名前を指定して子ノードを追加 */
                auto& child_node = out_node.add(name, "");

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素をシリアライズして子ノードに追加 */
                    this->Serialize(item, "item", child_node);
                }
            }

            /* std::map型デシリアライズ */
            template <typename TKey, typename TValue>
            void Deserialize(const Node& in_node, const string_t& name, std::map<TKey, TValue>& out_data)
            {
                /* 名前を指定して子ノードを取得 */
                auto& child_node = in_node.get_child(name);

                /* 子ノードの全要素を走査 */
                for (const auto& item_node_pair : child_node)
                {
                    /* キー要素 */
                    TKey key{};

                    /* キー要素デシリアライズ */
                    this->Deserialize(item_node_pair.second, "first", key);

                    /* 値要素 */
                    TValue value{};

                    /* 値要素デシリアライズ */
                    this->Deserialize(item_node_pair.second, "second", value);

                    /* キー/値を追加 */
                    out_data.emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(value));
                }
            }

            /* クラス/構造体(class/struct)型メンバシリアライズ */
            template <typename TUPLE, size_t ...I>
            void SerializeTupleImple(Node& out_node, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallowイディオムでクラス/構造体(class/struct)型メンバのタプルを順次展開し、シリアライズ */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Serialize(std::get<1>(std::get<I>(t)), std::get<0>(std::get<I>(t)), out_node)), 0)...
                };
            }

            /* クラス/構造体(class/struct)型メンバデシリアライズ */
            template <typename TUPLE, size_t ...I>
            void DeserializeTupleImple(const Node& in_node, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallowイディオムでクラス/構造体(class/struct)型メンバのタプルを順次展開し、デシリアライズ */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Deserialize(in_node, std::get<0>(std::get<I>(t)), std::get<1>(std::get<I>(t)))), 0)...
                };
            }

            /* クラス/構造体(class/struct)型メンバタプルシリアライズ */
            template <typename TUPLE>
            void SerializeTuple(Node& out_node, TUPLE&& t)
            {
                /* クラス/構造体(class/struct)型メンバシリアライズ */
                this->SerializeTupleImple(out_node, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* クラス/構造体(class/struct)型メンバタプルデシリアライズ */
            template <typename TUPLE>
            void DeserializeTuple(const Node& in_node, TUPLE&& t)
            {
                /* クラス/構造体(class/struct)型メンバデシリアライズ */
                this->DeserializeTupleImple(in_node, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }


            /* クラス/構造体(class/struct)型シリアライズ */
            template<class T>
            void Serialize(const T& in_data, Node& out_node, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* メンバの名前付きタプル取得 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetNamedMembersAsTuple(in_data);

                /* メンバの名前付きタプルから各メンバをシリアライズ */
                this->SerializeTuple(out_node, tuple);
            }

            /* クラス/構造体(class/struct)型デシリアライズ */
            template<class T>
            void Deserialize(const Node& in_node, T& out_data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* メンバの名前付きタプル取得 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetNamedMembersAsTuple(out_data);

                /* メンバの名前付きタプルから各メンバをデシリアライズ */
                this->DeserializeTuple(in_node, tuple);
            }


            /* 名前付きオブジェクトシリアライズ */
            template <typename T>
            void Serialize(const T& in_data, const string_t& name, Node& out_node)
            {
                /* ツリーノードに名前を指定して子ノード追加 */
                auto& child_node = out_node.add(name, "");

                /* 入力データをシリアライズして子ノードに追加 */
                this->Serialize(in_data, child_node);
            }

            /* 名前付きオブジェクトデシリアライズ */
            template <typename T>
            void Deserialize(const Node& in_node, const string_t& name, T& out_data)
            {
                /* ツリーノードに名前を指定して子ノード取得 */
                auto& child_node = in_node.get_child(name);

                /* 子ノードからデータをデシリアライズ */
                this->Deserialize(child_node, out_data);
            }

        private:
            /* 文字列型シリアライズ */
            inline void Serialize(const string_t& in_data, Node& out_node)
            {
                /* ツリーノードに値を追加 */
                out_node.put_value(in_data);
            }

            /* 文字列型デシリアライズ */
            inline void Deserialize(const Node& in_node, string_t& out_data)
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
            inline void WriteText(const Node& in_root_node, serialization::Archive& out_archive)
            {
                /* 文字列ストリーム */
                std::stringstream ss;

#if TEXT_SERIALIZE_MODE == TEXT_SERIALIZE_MODE_XML
                /* インデントサイズ */
                const int indent = 2;

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
            inline void ReadText(const serialization::Archive& in_archive, Node& out_root_node)
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
            inline void ToHexString(const float32_t& in_data, string_t& out_data)
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
            inline void ToHexString(const float64_t& in_data, string_t& out_data)
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
            inline void FromHexString(const string_t& in_data, float32_t& out_data)
            {
                /* 16進数文字列を整数に変換 */
                uint32_t int_data = std::stoul(in_data, nullptr, 16);

                /* 浮動小数 <=> 整数変換器 */
                cpp_lib::binary::FloatIntConverter<float32_t, uint32_t> converter;

                /* 整数 => 浮動小数変換 */
                out_data = converter.ConvertToFloat(int_data);
            }

            /* 16進数文字列を浮動小数(64bit)データに変換 */
            inline void FromHexString(const string_t& in_data, float64_t& out_data)
            {
                /* 16進数文字列を整数に変換 */
                uint64_t int_data = std::stoull(in_data, nullptr, 16);

                /* 浮動小数 <=> 整数変換器 */
                cpp_lib::binary::FloatIntConverter<float64_t, uint64_t> converter;

                /* 整数 => 浮動小数変換 */
                out_data = converter.ConvertToFloat(int_data);
            }
        };
    }
}
