#pragma once
#include "TypeTraits.h"

#include <random>
#include <ctime>
#include <type_traits>

/* �����������[�h */
#define RANDOM_GENERATE_MODE_NORMAL     (0) /* �m�[�}�� */
#define RANDOM_GENERATE_MODE_NO_ZERO    (1) /* �[��(0)������ */
#define RANDOM_GENERATE_MODE_MANUAL     (2) /* �}�j���A��(�����Ŏw��) */

/* �����������[�h�R���t�B�O */
#define RANDOM_GENERATE_MODE            (RANDOM_GENERATE_MODE_NO_ZERO)

namespace util
{
    namespace random
    {
        class RandomGenerator
        {
        public:
            static RandomGenerator& GetInstance();

        private:
            RandomGenerator();

            ~RandomGenerator() = default;

        public:
            RandomGenerator(const RandomGenerator&) = delete;
            RandomGenerator(RandomGenerator&&) = delete;
            RandomGenerator& operator=(const RandomGenerator&) = delete;
            RandomGenerator& operator=(RandomGenerator&&) = delete;

        public:
            /* �����^�������� */
            template <typename T, typename util::type_traits::concept_t<std::is_integral<T>::value> = nullptr>
            T GenerateInt(T min, T max, bool no_zero)
            {
                if (no_zero == true)
                {
                    T value = 0;

                    while (true)
                    {
                        std::uniform_int<T> rand(min, max);

                        value = rand(this->m_MT);

                        if (value != 0)
                        {
                            break;
                        }
                    }

                    return value;
                }
                else
                {
                    std::uniform_int<T> rand(min, max);

                    return rand(this->m_MT);
                }
            }

            /* ���������^�������� */
            template <typename T, typename util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
            T GenerateFloat(T min, T max, bool no_zero)
            {
                if (no_zero == true)
                {
                    T value = 0.0;

                    while (true)
                    {
                        std::uniform_real<T> rand(min, max);

                        value = rand(this->m_MT);

                        if (value != 0.0)
                        {
                            break;
                        }
                    }

                    return value;
                }
                else
                {
                    std::uniform_real<T> rand(min, max);

                    return rand(this->m_MT);
                }
            }

            /* �񋓌^(enum/enum class)�������� */
            template <typename T, typename util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            T GenerateEnum(T min, T max, bool no_zero)
            {
                if (no_zero == true)
                {
                    util::type_traits::underlying_type_t<T> value = 0;

                    while (true)
                    {
                        std::uniform_int<util::type_traits::underlying_type_t<T>> rand(util::type_traits::underlying_cast<T>(min), util::type_traits::underlying_cast<T>(max));

                        value = rand(this->m_MT);

                        if (value != 0)
                        {
                            break;
                        }
                    }

                    return value;
                }
                else
                {
                    std::uniform_int<util::type_traits::underlying_type_t<T>> rand(util::type_traits::underlying_cast<T>(min), util::type_traits::underlying_cast<T>(max));

                    return rand(this->m_MT);
                }
            }

            /* �_���^(bool)�������� */
            bool GenerateBool(bool no_zero)
            {
                if (no_zero == true)
                {
                    return true;
                }
                else
                {
                    int random = this->GenerateInt(0, 1, false);

                    return (random == 0) ? false : true;
                }
            }

        private:
            std::random_device m_RandomDevice; /* Random Device */
            std::mt19937_64 m_MT; /* MT19937 */
        };
    }

    /* Generate Random Value Macro Function */
#if RANDOM_GENERATE_MODE == RANDOM_GENERATE_MODE_NORMAL
#define GET_RANDOM_INT(min, max)                util::random::RandomGenerator::GetInstance().GenerateInt(min, max, false)
#define GET_RANDOM_FLOAT(min, max)              util::random::RandomGenerator::GetInstance().GenerateFloat(min, max, false)
#define GET_RANDOM_ENUM(min, max)               util::random::RandomGenerator::GetInstance().GenerateEnum(min, max, false)
#define GET_RANDOM_BOOL()                       util::random::RandomGenerator::GetInstance().GenerateBool(false)
#elif RANDOM_GENERATE_MODE == RANDOM_GENERATE_MODE_NO_ZERO
#define GET_RANDOM_INT(min, max)                util::random::RandomGenerator::GetInstance().GenerateInt(min, max, true)
#define GET_RANDOM_FLOAT(min, max)              util::random::RandomGenerator::GetInstance().GenerateFloat(min, max, true)
#define GET_RANDOM_ENUM(min, max)               util::random::RandomGenerator::GetInstance().GenerateEnum(min, max, true)
#define GET_RANDOM_BOOL()                       util::random::RandomGenerator::GetInstance().GenerateBool(true)
#elif RANDOM_GENERATE_MODE == RANDOM_GENERATE_MODE_MANUAL
#define GET_RANDOM_INT(min, max, no_zero)       util::random::RandomGenerator::GetInstance().GenerateInt(min, max, no_zero)
#define GET_RANDOM_FLOAT(min, max, no_zero)     util::random::RandomGenerator::GetInstance().GenerateFloat(min, max, no_zero)
#define GET_RANDOM_ENUM(min, max, no_zero)      util::random::RandomGenerator::GetInstance().GenerateEnum(min, max, no_zero)
#define GET_RANDOM_BOOL(no_zero)                util::random::RandomGenerator::GetInstance().GenerateBool(no_zero)
#else
#define GET_RANDOM_INT(min, max)                util::random::RandomGenerator::GetInstance().GenerateInt(min, max, false)
#define GET_RANDOM_FLOAT(min, max)              util::random::RandomGenerator::GetInstance().GenerateFloat(min, max, false)
#define GET_RANDOM_ENUM(min, max)               util::random::RandomGenerator::GetInstance().GenerateEnum(min, max, false)
#define GET_RANDOM_BOOL()                       util::random::RandomGenerator::GetInstance().GenerateBool(false)
#endif
}