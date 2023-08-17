#include "UserDataTypes.h"
#include "UserTypeOperations.h"
#include "SerializerFactory.h"
#include "DataDumper.h"
#include "RandomDataGenerator.h"

#include <iostream>

#define SERIALIZE_MODE_BINARY   (0)
#define SERIALIZE_MODE_TEXT     (1)

#define SERIALIZE_MODE          (SERIALIZE_MODE_BINARY)

template <typename T>
void SerializeTest(const std::string& type_name)
{
    std::stringstream ss;

    T in_data{};

    ss << "Serialize Test : " << type_name << std::endl;

    cpp_lib::random::RandomDataGenerator::Generate(in_data);

    ss << "-----Before Dump----" << std::endl;
    ss << cpp_lib::dump::DataDumper::ToString(type_name, in_data);
    ss << "--------------------" << std::endl;

#if SERIALIZE_MODE == SERIALIZE_MODE_TEXT
    cpp_lib::serialization::Serializer<T>& serializer = cpp_lib::serialization::SerializerFactory<T>::CreateTextSerializer();
#else
    cpp_lib::serialization::Serializer<T>& serializer = cpp_lib::serialization::SerializerFactory<T>::CreateBinarySerializer();
#endif

    cpp_lib::serialization::Archive archive;

    serializer.Serialize(in_data, archive);

    ss << std::endl;
    ss << "Serialized Size : " << archive.GetSize() << std::endl;
#if SERIALIZE_MODE == SERIALIZE_MODE_TEXT
    ss << "------XML Dump------" << std::endl;
    ss << archive.GetDataPtr();
    ss << "--------------------" << std::endl;
#endif

    ss << std::endl;

    T out_data{};

    serializer.Deserialize(archive, out_data);

    ss << "-----After Dump----" << std::endl;
    ss << cpp_lib::dump::DataDumper::ToString(type_name, out_data);
    ss << "--------------------" << std::endl;;

    std::cout << ss.str() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
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


