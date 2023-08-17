#pragma once
#include "TypeTraits.h"

#include <random>
#include <ctime>
#include <type_traits>

/* 乱数生成モード */
#define RANDOM_GENERATE_MODE_NORMAL     (0) /* ノーマル */
#define RANDOM_GENERATE_MODE_NO_ZERO    (1) /* ゼロ(0)を除く */
#define RANDOM_GENERATE_MODE_MANUAL     (2) /* マニュアル(引数で指定) */

/* 乱数生成モードコンフィグ */
#define RANDOM_GENERATE_MODE            (RANDOM_GENERATE_MODE_NO_ZERO)

namespace cpp_lib
{
    namespace random
    {
        /* 乱数生成クラス */
        class RandomGenerator
        {
        public:
            /* シングルトンインスタンス取得 */
            static RandomGenerator& GetInstance();

        private:
            /* コンストラクタ */
            RandomGenerator();

            /* デストラクタ */
            ~RandomGenerator() = default;

        public:
            /* コピー&ムーブセマンティクス無効化 */
            RandomGenerator(const RandomGenerator&) = delete;
            RandomGenerator(RandomGenerator&&) = delete;
            RandomGenerator& operator=(const RandomGenerator&) = delete;
            RandomGenerator& operator=(RandomGenerator&&) = delete;

        public:
            /* 整数型乱数生成 */
            template <typename T, typename cpp_lib::type_traits::concept_t<std::is_integral<T>::value> = nullptr>
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

            /* 浮動小数型乱数生成 */
            template <typename T, typename cpp_lib::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
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

            /* 列挙型(enum/enum class)乱数生成 */
            template <typename T, typename cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            T GenerateEnum(T min, T max, bool no_zero)
            {
                if (no_zero == true)
                {
                    cpp_lib::type_traits::underlying_type_t<T> value = 0;

                    while (true)
                    {
                        std::uniform_int<cpp_lib::type_traits::underlying_type_t<T>> rand(cpp_lib::type_traits::underlying_cast<T>(min), cpp_lib::type_traits::underlying_cast<T>(max));

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
                    std::uniform_int<cpp_lib::type_traits::underlying_type_t<T>> rand(cpp_lib::type_traits::underlying_cast<T>(min), cpp_lib::type_traits::underlying_cast<T>(max));

                    return rand(this->m_MT);
                }
            }

            /* 論理型(bool)乱数生成 */
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
            /* ランダムデバイス */
            std::random_device m_RandomDevice;

            /* 64bit MT19937(メルセンヌ・ツイスターエンジン) */
            std::mt19937_64 m_MT;
        };
    }

/* 乱数生成マクロ関数 */
#if RANDOM_GENERATE_MODE == RANDOM_GENERATE_MODE_NORMAL
#define GET_RANDOM_INT(min, max)                cpp_lib::random::RandomGenerator::GetInstance().GenerateInt(min, max, false)
#define GET_RANDOM_FLOAT(min, max)              cpp_lib::random::RandomGenerator::GetInstance().GenerateFloat(min, max, false)
#define GET_RANDOM_ENUM(min, max)               cpp_lib::random::RandomGenerator::GetInstance().GenerateEnum(min, max, false)
#define GET_RANDOM_BOOL()                       cpp_lib::random::RandomGenerator::GetInstance().GenerateBool(false)
#elif RANDOM_GENERATE_MODE == RANDOM_GENERATE_MODE_NO_ZERO
#define GET_RANDOM_INT(min, max)                cpp_lib::random::RandomGenerator::GetInstance().GenerateInt(min, max, true)
#define GET_RANDOM_FLOAT(min, max)              cpp_lib::random::RandomGenerator::GetInstance().GenerateFloat(min, max, true)
#define GET_RANDOM_ENUM(min, max)               cpp_lib::random::RandomGenerator::GetInstance().GenerateEnum(min, max, true)
#define GET_RANDOM_BOOL()                       cpp_lib::random::RandomGenerator::GetInstance().GenerateBool(true)
#elif RANDOM_GENERATE_MODE == RANDOM_GENERATE_MODE_MANUAL
#define GET_RANDOM_INT(min, max, no_zero)       cpp_lib::random::RandomGenerator::GetInstance().GenerateInt(min, max, no_zero)
#define GET_RANDOM_FLOAT(min, max, no_zero)     cpp_lib::random::RandomGenerator::GetInstance().GenerateFloat(min, max, no_zero)
#define GET_RANDOM_ENUM(min, max, no_zero)      cpp_lib::random::RandomGenerator::GetInstance().GenerateEnum(min, max, no_zero)
#define GET_RANDOM_BOOL(no_zero)                cpp_lib::random::RandomGenerator::GetInstance().GenerateBool(no_zero)
#else
#define GET_RANDOM_INT(min, max)                cpp_lib::random::RandomGenerator::GetInstance().GenerateInt(min, max, false)
#define GET_RANDOM_FLOAT(min, max)              cpp_lib::random::RandomGenerator::GetInstance().GenerateFloat(min, max, false)
#define GET_RANDOM_ENUM(min, max)               cpp_lib::random::RandomGenerator::GetInstance().GenerateEnum(min, max, false)
#define GET_RANDOM_BOOL()                       cpp_lib::random::RandomGenerator::GetInstance().GenerateBool(false)
#endif
}
