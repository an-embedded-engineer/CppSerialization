#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "RandomGenerator.h"

#define MIN_CONTAINER_SIZE  (1)     /* Min Container Size */
#define MAX_CONTAINER_SIZE  (30)    /* Max Container Size */

namespace debug
{
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
        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        static void Generate(T& data);


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

        /* �N���X/�\����(class/struct)�^�����f�[�^���� */
        template<typename T, util::type_traits::concept_t<std::is_class<T>::value> = nullptr>
        static void Generate(T& data);

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
