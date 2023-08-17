#pragma once
#include "RandomDataGenerator.h"
#include "DomainModelDataTypes.h"

namespace debug
{
    /* �����I�C���X�^���X�� */
    /* �\����(struct) */
    template void RandomDataGenerator::Generate<dm::StrucMessage1>(dm::StrucMessage1& data);
    template void RandomDataGenerator::Generate<dm::StrucMessage2>(dm::StrucMessage2& data);
    template void RandomDataGenerator::Generate<dm::StrucMessage3>(dm::StrucMessage3& data);
    /* �񋓑�(enum/enum class) */
    template void RandomDataGenerator::Generate<dm::EnumType1>(dm::EnumType1& data);
    template void RandomDataGenerator::Generate<dm::EnumMessage1>(dm::EnumMessage1& data);
    template void RandomDataGenerator::Generate<dm::EnumMessage2>(dm::EnumMessage2& data);
}
