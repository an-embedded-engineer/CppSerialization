#include "RandomGenerator.h"

namespace util
{
    namespace random
    {
        /* Get Singleton Instance */
        RandomGenerator& RandomGenerator::GetInstance()
        {
            static RandomGenerator instance;
            return instance;
        }

        /* Constructor */
        RandomGenerator::RandomGenerator()
            : m_RandomDevice()
            , m_MT(m_RandomDevice())
        {
            /* Nothing to do */
        }
    }
}
