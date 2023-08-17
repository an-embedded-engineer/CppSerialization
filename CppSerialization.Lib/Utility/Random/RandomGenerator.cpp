#include "RandomGenerator.h"

namespace util
{
    namespace random
    {
        /* �V���O���g���C���X�^���X�擾 */
        RandomGenerator& RandomGenerator::GetInstance()
        {
            static RandomGenerator instance;
            return instance;
        }

        /* �R���X�g���N�^ */
        RandomGenerator::RandomGenerator()
            : m_RandomDevice()
            , m_MT(m_RandomDevice())
        {
            /* Nothing to do */
        }
    }
}
