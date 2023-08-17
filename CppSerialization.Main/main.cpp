#include "DomainModelDataTypes.h"
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

    debug::RandomDataGenerator::Generate(in_data);

    ss << "-----Before Dump----" << std::endl;
    ss << debug::DataDumper::ToString(type_name, in_data);
    ss << "--------------------" << std::endl;

#if SERIALIZE_MODE == SERIALIZE_MODE_TEXT
    serialization::Serializer<T>& serializer = serialization::SerializerFactory<T>::CreateTextSerializer();
#else
    serialization::Serializer<T>& serializer = serialization::SerializerFactory<T>::CreateBinarySerializer();
#endif

    serialization::Archive archive;

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
    ss << debug::DataDumper::ToString(type_name, out_data);
    ss << "--------------------" << std::endl;;

    std::cout << ss.str() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
    SerializeTest<dm::BoolMessage>("BoolMessage");
    SerializeTest<dm::Int8Message>("Int8Message");
    SerializeTest<dm::Int16Message>("Int16Message");
    SerializeTest<dm::Int32Message>("Int32Message");
    SerializeTest<dm::Int64Message>("Int64Message");
    SerializeTest<dm::UInt8Message>("UInt8Message");
    SerializeTest<dm::UInt16Message>("UInt16Message");
    SerializeTest<dm::UInt32Message>("UInt32Message");
    SerializeTest<dm::UInt64Message>("UInt64Message");
    SerializeTest<dm::Float32Message>("Float32Message");
    SerializeTest<dm::Float64Message>("Float64Message");
    SerializeTest<dm::StringMessage>("StringMessage");
    SerializeTest<dm::ArrayMessage>("ArrayMessage");
    SerializeTest<dm::VectorMessage>("VectorMessage");
    SerializeTest<dm::MapMessage>("MapMessage");
    SerializeTest<dm::EnumMessage1>("EnumMessage1");
    SerializeTest<dm::EnumMessage2>("EnumMessage2");
    SerializeTest<dm::StrucMessage1>("StrucMessage1");
    SerializeTest<dm::StrucMessage2>("StrucMessage2");
    SerializeTest<dm::StrucMessage3>("StrucMessage3");

    return 0;
}


