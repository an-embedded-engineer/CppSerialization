#include "RandomDataGenerator.h"
#include "RandomGenerator.h"
#include <sstream>

#define MINUS_VALUE_ENABLED (0) /* �����f�[�^�������̕��l�L���� */

namespace cpp_lib
{
    namespace random
    {
        /* �Z�p�^�p�ő�/�ŏ��l */
#if MINUS_VALUE_ENABLED == 1
        constexpr int8_t    SInt8Min = -100;
        constexpr int8_t    SInt8Max = 100;
        constexpr int16_t   SInt16Min = -1000;
        constexpr int16_t   SInt16Max = 1000;
        constexpr int32_t   SInt32Min = -1000;
        constexpr int32_t   SInt32Max = 1000;
        constexpr int64_t   SInt64Min = -1000;
        constexpr int64_t   SInt64Max = 1000;
        constexpr uint8_t   UInt8Min = 0;
        constexpr uint8_t   UInt8Max = 200;
        constexpr uint16_t  UInt16Min = 0;
        constexpr uint16_t  UInt16Max = 2000;
        constexpr uint32_t  UInt32Min = 0;
        constexpr uint32_t  UInt32Max = 2000;
        constexpr uint64_t  UInt64Min = 0;
        constexpr uint64_t  UInt64Max = 2000;
        constexpr float32_t Float32Min = -1000.0f;
        constexpr float32_t Float32Max = 1000.0f;
        constexpr float64_t Float64Min = -1000.0;
        constexpr float64_t Float64Max = 1000.0;
#else
        constexpr int8_t    SInt8Min = 0;
        constexpr int8_t    SInt8Max = 100;
        constexpr int16_t   SInt16Min = 0;
        constexpr int16_t   SInt16Max = 1000;
        constexpr int32_t   SInt32Min = 0;
        constexpr int32_t   SInt32Max = 1000;
        constexpr int64_t   SInt64Min = 0;
        constexpr int64_t   SInt64Max = 1000;
        constexpr uint8_t   UInt8Min = 0;
        constexpr uint8_t   UInt8Max = 200;
        constexpr uint16_t  UInt16Min = 0;
        constexpr uint16_t  UInt16Max = 2000;
        constexpr uint32_t  UInt32Min = 0;
        constexpr uint32_t  UInt32Max = 2000;
        constexpr uint64_t  UInt64Min = 0;
        constexpr uint64_t  UInt64Max = 2000;
        constexpr float32_t Float32Min = 0.0f;
        constexpr float32_t Float32Max = 1000.0f;
        constexpr float64_t Float64Min = 0.0;
        constexpr float64_t Float64Max = 1000.0;
#endif

        /* �_���^(bool)�����f�[�^���� */
        void RandomDataGenerator::Generate(bool& data)
        {
            data = GET_RANDOM_BOOL();
        }

        /* 8bit�����t�����^(int8)�����f�[�^���� */
        void RandomDataGenerator::Generate(int8_t& data)
        {
            data = GET_RANDOM_INT(SInt8Min, SInt8Max);
        }

        /* 16bit�����t�����^(int16)�����f�[�^���� */
        void RandomDataGenerator::Generate(int16_t& data)
        {
            data = GET_RANDOM_INT(SInt16Min, SInt16Max);
        }

        /* 32bit�����t�����^(int32)�����f�[�^���� */
        void RandomDataGenerator::Generate(int32_t& data)
        {
            data = GET_RANDOM_INT(SInt32Min, SInt32Max);
        }

        /* 64bit�����t�����^(int64)�����f�[�^���� */
        void RandomDataGenerator::Generate(int64_t& data)
        {
            data = GET_RANDOM_INT(SInt64Min, SInt64Max);
        }

        /* 8bit�����������^(uint8)�����f�[�^���� */
        void RandomDataGenerator::Generate(uint8_t& data)
        {
            data = GET_RANDOM_INT(UInt8Min, UInt8Max);
        }

        /* 16bit�����������^(uint16)�����f�[�^���� */
        void RandomDataGenerator::Generate(uint16_t& data)
        {
            data = GET_RANDOM_INT(UInt16Min, UInt16Max);
        }

        /* 32bit�����������^(uint32)�����f�[�^���� */
        void RandomDataGenerator::Generate(uint32_t& data)
        {
            data = GET_RANDOM_INT(UInt32Min, UInt32Max);
        }

        /* 64bit�����������^(uint64)�����f�[�^���� */
        void RandomDataGenerator::Generate(uint64_t& data)
        {
            data = GET_RANDOM_INT(UInt64Min, UInt64Max);
        }

        /* 32bit���������^(float)�����f�[�^���� */
        void RandomDataGenerator::Generate(float32_t& data)
        {
            data = GET_RANDOM_FLOAT(Float32Min, Float32Max);
        }

        /* 32bit���������^(double)�����f�[�^���� */
        void RandomDataGenerator::Generate(float64_t& data)
        {
            data = GET_RANDOM_FLOAT(Float64Min, Float64Max);
        }

        /* ������^(string)�����f�[�^���� */
        void RandomDataGenerator::Generate(std::string& data)
        {
            /* �����f�[�^�Ƃ��Ďg�p���镶�����X�g */
            const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

            /* �����f�[�^�Ƃ��Ďg�p���镶�����X�g�̒������擾 */
            const size_t chars_length = chars.length();

            /* �����f�[�^�Ƃ��Đ������镶����̒����������_���ɎZ�o */
            int data_length = GET_RANDOM_INT(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE);

            std::stringstream ss;

            /* ������̒������J��Ԃ� */
            for (int i = 0; i < data_length; i++)
            {
                /* �����f�[�^�Ƃ��Ďg�p���镶�����X�g�̃C���f�b�N�X�������_���ɑI�o */
                int index = GET_RANDOM_INT(0, static_cast<int>(chars_length - 1));

                /* �����f�[�^�Ƃ��Ďg�p���镶�����X�g�̎w��C���f�b�N�X�̕�����ǉ� */
                ss << chars[index];
            }

            /* ������ɕϊ� */
            data = ss.str();
        }
    }
}
