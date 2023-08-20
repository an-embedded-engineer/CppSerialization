#include "UserDataTypes.h"
#include "UserTypeOperations.h"

#include <iostream>

/* シリアライズモード：バイナリ形式 */
#define SERIALIZE_MODE_BINARY   (0)
/* シリアライズモード：テキスト形式 */
#define SERIALIZE_MODE_TEXT     (1)

/* シリアライズモード切替え */
#define SERIALIZE_MODE          (SERIALIZE_MODE_TEXT)

/* シリアライズテスト */
template <typename T>
void SerializeTest(const std::string& type_name)
{
    /* ログダンプ用文字列ストリーム */
    std::stringstream ss;

    /* 入力データ */
    T in_data{};

    ss << "Serialize Test : " << type_name << std::endl;

    /* 入力データを乱数で生成 */
    cpp_lib::random::RandomDataGenerator::Generate(in_data);

    ss << "-----Before Dump----" << std::endl;
    /* 入力データをダンプ */
    ss << cpp_lib::dump::DataDumper::ToString(type_name, in_data);
    ss << "--------------------" << std::endl;

#if SERIALIZE_MODE == SERIALIZE_MODE_BINARY
    /* バイナリ形式用シリアライザインスタンス生成 */
    cpp_lib::serialization::Serializer<T>& serializer = cpp_lib::serialization::SerializerFactory<T>::CreateBinarySerializer();
#elif SERIALIZE_MODE == SERIALIZE_MODE_TEXT
    /* テキスト形式用シリアライザインスタンス生成 */
    cpp_lib::serialization::Serializer<T>& serializer = cpp_lib::serialization::SerializerFactory<T>::CreateTextSerializer();
#else
#error Invalid Serialize Mode : SERIALIZE_MODE
#endif

    /* アーカイブ */
    cpp_lib::serialization::Archive archive;

    /* シリアライズ */
    serializer.Serialize(in_data, archive);

    /* シリアライズ後のデータサイズ出力 */
    ss << std::endl;
    ss << "Serialized Size : " << archive.GetSize() << std::endl;

    /* テキスト形式の場合はテキストデータをダンプ */
#if SERIALIZE_MODE == SERIALIZE_MODE_TEXT
    ss << "------XML Dump------" << std::endl;
    ss << archive.GetDataPtr();
    ss << "--------------------" << std::endl;
#endif

    ss << std::endl;

    /* 出力データ */
    T out_data{};

    /* アーカイブをデシリアライズ */
    serializer.Deserialize(archive, out_data);

    ss << "-----After Dump----" << std::endl;
    /* 出力データをダンプ */
    ss << cpp_lib::dump::DataDumper::ToString(type_name, out_data);
    ss << "--------------------" << std::endl;;

    /* 文字列ストリームをコンソールに出力 */
    std::cout << ss.str() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
    /* 各ユーザ定義型に対するシリアライズテスト実行 */
    SerializeTest<app::BoolMessage>("BoolMessage");
    SerializeTest<app::Int8Message>("Int8Message");
    SerializeTest<app::Int16Message>("Int16Message");
    SerializeTest<app::Int32Message>("Int32Message");
    SerializeTest<app::Int64Message>("Int64Message");
    SerializeTest<app::UInt8Message>("UInt8Message");
    SerializeTest<app::UInt16Message>("UInt16Message");
    SerializeTest<app::UInt32Message>("UInt32Message");
    SerializeTest<app::UInt64Message>("UInt64Message");
    SerializeTest<app::Float32Message>("Float32Message");
    SerializeTest<app::Float64Message>("Float64Message");
    SerializeTest<app::StringMessage>("StringMessage");
    SerializeTest<app::ArrayMessage>("ArrayMessage");
    SerializeTest<app::VectorMessage>("VectorMessage");
    SerializeTest<app::MapMessage>("MapMessage");
    SerializeTest<app::EnumMessage1>("EnumMessage1");
    SerializeTest<app::EnumMessage2>("EnumMessage2");
    SerializeTest<app::StrucMessage1>("StrucMessage1");
    SerializeTest<app::StrucMessage2>("StrucMessage2");
    SerializeTest<app::StrucMessage3>("StrucMessage3");

    return 0;
}


