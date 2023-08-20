#pragma once
/* 型定義&型特性定義 */
#include "UserDataTypes.h"
#include "UserDataTypeTraits.h"

/* シリアライザ */
#include "BinarySerialization.h"
#include "TextSerialization.h"
#include "Serializer.h"
#include "SerializerFactory.h"


/* データダンプ */
#include "DataDumper.h"

/* 乱数データ生成 */
#include "RandomDataGenerator.h"

namespace cpp_lib
{
    namespace serialization
    {
        /* バイナリ形式シリアライズ明示的インスタンス化宣言 */
        /* app::StrucMessage1 */
        extern template void BinarySerialization::Calculate<app::StrucMessage1>(const app::StrucMessage1& in_data, size_t& out_size, typename std::enable_if<std::is_class<app::StrucMessage1>::value>::type*);
        extern template void BinarySerialization::Serialize<app::StrucMessage1>(const app::StrucMessage1& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<app::StrucMessage1>::value>::type*);
        extern template void BinarySerialization::Deserialize<app::StrucMessage1>(const serialization::Archive& in_archive, size_t& offset, app::StrucMessage1& out_data, typename std::enable_if<std::is_class<app::StrucMessage1>::value>::type*);

        /* app::StrucMessage2 */
        extern template void BinarySerialization::Calculate<app::StrucMessage2>(const app::StrucMessage2& in_data, size_t& out_size, typename std::enable_if<std::is_class<app::StrucMessage2>::value>::type*);
        extern template void BinarySerialization::Serialize<app::StrucMessage2>(const app::StrucMessage2& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<app::StrucMessage2>::value>::type*);
        extern template void BinarySerialization::Deserialize<app::StrucMessage2>(const serialization::Archive& in_archive, size_t& offset, app::StrucMessage2& out_data, typename std::enable_if<std::is_class<app::StrucMessage2>::value>::type*);

        /* app::StrucMessage3 */
        extern template void BinarySerialization::Calculate<app::StrucMessage3>(const app::StrucMessage3& in_data, size_t& out_size, typename std::enable_if<std::is_class<app::StrucMessage3>::value>::type*);
        extern template void BinarySerialization::Serialize<app::StrucMessage3>(const app::StrucMessage3& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<app::StrucMessage3>::value>::type*);
        extern template void BinarySerialization::Deserialize<app::StrucMessage3>(const serialization::Archive& in_archive, size_t& offset, app::StrucMessage3& out_data, typename std::enable_if<std::is_class<app::StrucMessage3>::value>::type*);


        /* テキスト形式シリアライズ明示的インスタンス化宣言 */
        /* app::StrucMessage1 */
        extern template void TextSerialization::Serialize<app::StrucMessage1>(const app::StrucMessage1& in_data, Node& out_node, typename std::enable_if<std::is_class<app::StrucMessage1>::value>::type*);
        extern template void TextSerialization::Deserialize<app::StrucMessage1>(const Node& in_node, app::StrucMessage1& out_data, typename std::enable_if<std::is_class<app::StrucMessage1>::value>::type*);

        /* app::StrucMessage2 */
        extern template void TextSerialization::Serialize<app::StrucMessage2>(const app::StrucMessage2& in_data, Node& out_node, typename std::enable_if<std::is_class<app::StrucMessage2>::value>::type*);
        extern template void TextSerialization::Deserialize<app::StrucMessage2>(const Node& in_node, app::StrucMessage2& out_data, typename std::enable_if<std::is_class<app::StrucMessage2>::value>::type*);

        /* app::StrucMessage3 */
        extern template void TextSerialization::Serialize<app::StrucMessage3>(const app::StrucMessage3& in_data, Node& out_node, typename std::enable_if<std::is_class<app::StrucMessage3>::value>::type*);
        extern template void TextSerialization::Deserialize<app::StrucMessage3>(const Node& in_node, app::StrucMessage3& out_data, typename std::enable_if<std::is_class<app::StrucMessage3>::value>::type*);
    }

    namespace dump
    {
        /* データダンプ明示的インスタンス化宣言 */
        extern template void DataDumper::Dump<app::StrucMessage1>(const app::StrucMessage1& data, const size_t depth, std::stringstream& ss, typename std::enable_if<std::is_class<app::StrucMessage1>::value>::type*);
        extern template void DataDumper::Dump<app::StrucMessage2>(const app::StrucMessage2& data, const size_t depth, std::stringstream& ss, typename std::enable_if<std::is_class<app::StrucMessage2>::value>::type*);
        extern template void DataDumper::Dump<app::StrucMessage3>(const app::StrucMessage3& data, const size_t depth, std::stringstream& ss, typename std::enable_if<std::is_class<app::StrucMessage3>::value>::type*);
    }

    namespace random
    {
        /* 明示的インスタンス化宣言 */
        /* 構造体(struct) */
        extern template void RandomDataGenerator::Generate<app::StrucMessage1>(app::StrucMessage1& data, typename std::enable_if<std::is_class<app::StrucMessage1>::value>::type*);
        extern template void RandomDataGenerator::Generate<app::StrucMessage2>(app::StrucMessage2& data, typename std::enable_if<std::is_class<app::StrucMessage2>::value>::type*);
        extern template void RandomDataGenerator::Generate<app::StrucMessage3>(app::StrucMessage3& data, typename std::enable_if<std::is_class<app::StrucMessage3>::value>::type*);
        /* 列挙体(enum/enum class) */
        extern template void RandomDataGenerator::Generate<app::EnumType1>(app::EnumType1& data, typename std::enable_if<std::is_enum<app::EnumType1>::value>::type*);
        extern template void RandomDataGenerator::Generate<app::EnumMessage1>(app::EnumMessage1& data, typename std::enable_if<std::is_enum<app::EnumMessage1>::value>::type*);
        extern template void RandomDataGenerator::Generate<app::EnumMessage2>(app::EnumMessage2& data, typename std::enable_if<std::is_enum<app::EnumMessage2>::value>::type*);
    }
}
