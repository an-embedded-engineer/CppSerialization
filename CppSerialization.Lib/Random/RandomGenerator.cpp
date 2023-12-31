#include "RandomGenerator.h"

namespace cpp_lib
{
    namespace random
    {
        /* シングルトンインスタンス取得 */
        RandomGenerator& RandomGenerator::GetInstance()
        {
            static RandomGenerator instance;
            return instance;
        }

        /* コンストラクタ */
        RandomGenerator::RandomGenerator()
            : m_RandomDevice()
            , m_MT(m_RandomDevice())
        {
            /* Nothing to do */
        }
    }
}
