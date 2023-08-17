#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "DataTypeTraits.h"
#include "RandomGenerator.h"

/* �����f�[�^�������̃R���e�i�ő�/�ŏ��T�C�Y */
#define MIN_CONTAINER_SIZE  (1)     /* �ŏ��R���e�i�T�C�Y */
#define MAX_CONTAINER_SIZE  (30)    /* �ő�R���e�i�T�C�Y */

namespace cpp_lib
{
    namespace random
    {
        /* �����f�[�^�����N���X */
        class RandomDataGenerator
        {
        public:
            /* std::array�^�����f�[�^���� */
            template <typename T, size_t N>
            static void Generate(std::array<T, N>& data)
            {
                size_t size = N;

                for (size_t i = 0; i < size; i++)
                {
                    T item{};

                    RandomDataGenerator::Generate(item);

                    data[i] = item;
                }
            }

            /* std::vector�^�����f�[�^���� */
            template <typename T>
            static void Generate(std::vector<T>& data)
            {
                size_t size = GET_RANDOM_INT(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE);

                data.reserve(size);

                for (size_t i = 0; i < size; i++)
                {
                    T item{};

                    RandomDataGenerator::Generate(item);

                    data.push_back(item);
                }
            }

            /* std::pair�^�����f�[�^���� */
            template <typename T1, typename T2>
            static void Generate(std::pair<T1, T2>& data)
            {
                T1 first{};
                T2 second{};

                RandomDataGenerator::Generate(first);
                RandomDataGenerator::Generate(second);

                data = { first, second };
            }

            /* std::map�^�����f�[�^���� */
            template <typename T1, typename T2>
            static void Generate(std::map<T1, T2>& data)
            {
                size_t size = GET_RANDOM_INT(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE);

                for (size_t i = 0; i < size; i++)
                {
                    T1 key{};
                    T2 value{};

                    RandomDataGenerator::Generate(key);
                    RandomDataGenerator::Generate(value);

                    data[key] = value;
                }
            }

            /* �񋓑�(enum/enum class)�^�����f�[�^���� */
            template<typename T>
            static void Generate(T& data, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr)
            {
                /* EnumDataTypeTraits����enum�̍ő�/�ŏ��l���擾�����^�ɃL���X�g */
                cpp_lib::type_traits::underlying_type_t<T> min_value = cpp_lib::type_traits::underlying_cast<T>(cpp_lib::type_traits::EnumDataTypeTraits<T>::GetMinValue());
                cpp_lib::type_traits::underlying_type_t<T> max_value = cpp_lib::type_traits::underlying_cast<T>(cpp_lib::type_traits::EnumDataTypeTraits<T>::GetMaxValue());

                /* ���^�ŗ������� */
                cpp_lib::type_traits::underlying_type_t<T> underlying_data = GET_RANDOM_INT(min_value, max_value);

                /* ����enum/enum class�^�ɃL���X�g���ăZ�b�g */
                data = static_cast<T>(underlying_data);
            }


            /* �N���X/�\����(class/struct)�^�����o�����f�[�^���� */
            template <typename TUPLE, size_t ...I>
            static void GenerateTupleImple(TUPLE&& t, std::index_sequence<I...>)
            {
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(RandomDataGenerator::Generate(std::get<I>(t))), 0)...
                };
            }

            /* �N���X/�\����(class/struct)�^�����o�����f�[�^���� */
            template <typename TUPLE>
            static void GenerateTuple(TUPLE&& t)
            {
                RandomDataGenerator::GenerateTupleImple(std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* �N���X/�\����(class/struct)�^�����o�����f�[�^���� */
            template<typename T>
            static void Generate(T& data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* �����o�̃^�v���擾 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(data);

                /* �����o�̃^�v�����痐���f�[�^���� */
                RandomDataGenerator::GenerateTuple(tuple);
            }

        public:
            /* �_���^(bool)�����f�[�^���� */
            static void Generate(bool& data);

            /* 8bit�����t�����^(int8)�����f�[�^���� */
            static void Generate(int8_t& data);

            /* 16bit�����t�����^(int16)�����f�[�^���� */
            static void Generate(int16_t& data);

            /* 32bit�����t�����^(int32)�����f�[�^���� */
            static void Generate(int32_t& data);

            /* 64bit�����t�����^(int64)�����f�[�^���� */
            static void Generate(int64_t& data);

            /* 8bit�����������^(uint8)�����f�[�^���� */
            static void Generate(uint8_t& data);

            /* 16bit�����������^(uint16)�����f�[�^���� */
            static void Generate(uint16_t& data);

            /* 32bit�����������^(uint32)�����f�[�^���� */
            static void Generate(uint32_t& data);

            /* 64bit�����������^(uint64)�����f�[�^���� */
            static void Generate(uint64_t& data);

            /* 32bit���������^(float)�����f�[�^���� */
            static void Generate(float32_t& data);

            /* 32bit���������^(double)�����f�[�^���� */
            static void Generate(float64_t& data);

            /* ������^(string)�����f�[�^���� */
            static void Generate(std::string& data);
        };
    }
}
