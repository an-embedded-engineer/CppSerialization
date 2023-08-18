#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "DataTypeTraits.h"
#include "EndianType.h"
#include "Endian.h"
#include "Archive.h"
#include "BinaryConverter.h"

namespace cpp_lib
{
    namespace serialization
    {
        /* �o�C�i���`���V���A���C�Y�N���X */
        class BinarySerialization
        {
        public:
            /* �V���O���g���C���X�^���X�擾 */
            static BinarySerialization& GetInstance()
            {
                static BinarySerialization instance;
                return instance;
            }

        private:
            /* �R���X�g���N�^ */
            BinarySerialization()
                : m_CurrentEndian(cpp_lib::endian::GetEnvironmentEndian())
                , m_TargetEndian(cpp_lib::endian::EndianType::Network)
            {
                /* Nothing to do */
            }

            /* �f�X�g���N�^ */
            ~BinarySerialization() = default;

        public:
            /* �R�s�[&���[�u�Z�}���e�B�N�X������ */
            BinarySerialization(const BinarySerialization&) = delete;
            BinarySerialization(BinarySerialization&&) = delete;
            BinarySerialization& operator=(const BinarySerialization&) = delete;
            BinarySerialization& operator=(BinarySerialization&&) = delete;

        public:
            /* �V���A���C�Y��̃f�[�^�T�C�Y�Z�o */
            template <typename T>
            void CalculateSize(const T& in_data, size_t& out_size)
            {
                this->Calculate(in_data, out_size);
            }

            /* ���̓f�[�^���V���A���C�Y���ăA�[�J�C�u�ɕϊ� */
            template <typename T>
            void Serialize(const T& in_data, serialization::Archive& out_archive)
            {
                /* �V���A���C�Y��̃f�[�^�T�C�Y */
                size_t size = 0;

                /* �V���A���C�Y��̃f�[�^�T�C�Y�Z�o */
                this->CalculateSize(in_data, size);

                /* �V���A���C�Y��̃f�[�^�T�C�Y�ŃA�[�J�C�u�̃f�[�^�o�b�t�@�������m�� */
                out_archive.Reserve(size);

                /* �I�t�Z�b�g������ */
                size_t offset = 0;

                /* �V���A���C�Y */
                this->Serialize(in_data, offset, out_archive);
            }

            /* �A�[�J�C�u���f�V���A���C�Y���ďo�̓f�[�^�ɕϊ� */
            template <typename T>
            void Deserialize(const serialization::Archive& in_archive, T& out_data)
            {
                /* �I�t�Z�b�g������ */
                size_t offset = 0;

                /* �f�V���A���C�Y */
                this->Deserialize(in_archive, offset, out_data);
            }

        private:
            /* �Z�p�^�f�[�^�T�C�Y�Z�o */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            void Calculate(const T& in_data, size_t& out_size)
            {
                /* ���̓f�[�^�̌^�̃T�C�Y�����Z */
                out_size += sizeof(in_data);
            }

            /* �Z�p�^�V���A���C�Y */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            void Serialize(const T& in_data, size_t& offset, Archive& out_archive)
            {
                /* �o�C�g�z�� */
                std::array<byte_t, sizeof(T)> in_bytes{};

                /* ���̓f�[�^���o�C�g�z��ɕϊ�(�G���f�B�A���ɂ��K�v�ɉ����ăX���b�v) */
                cpp_lib::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, in_data, in_bytes);

                /* �w��I�t�Z�b�g�ʒu����o�C�g�z����A�[�J�C�u�ɏ������� */
                out_archive.Write(in_bytes, offset);
            }

            /* �Z�p�^�f�V���A���C�Y */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            void Deserialize(const Archive& in_archive, size_t& offset, T& out_data)
            {
                /* �o�C�g�z�� */
                std::array<byte_t, sizeof(T)> out_bytes{};

                /* �A�[�J�C�u�̎w��I�t�Z�b�g�ʒu����o�C�g�z��ǂݍ��� */
                in_archive.Read(out_bytes, offset);

                /* �o�C�g�z����o�̓f�[�^�ɕϊ�(�G���f�B�A���ɂ��K�v�ɉ����ăX���b�v) */
                cpp_lib::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, out_bytes, out_data);
            }

            /* �񋓌^(enum/enum class)�f�[�^�T�C�Y�Z�o */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Calculate(const T& in_data, size_t& out_size)
            {
                /* ���̓f�[�^�̊��^�̃T�C�Y�����Z */
                this->Calculate(cpp_lib::type_traits::underlying_cast(in_data), out_size);
            }

            /* �񋓌^(enum/enum class)�V���A���C�Y */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Serialize(const T& in_data, size_t& offset, Archive& out_archive)
            {
                /* ���̓f�[�^�̊��^�ɃL���X�g���ăV���A���C�Y */
                this->Serialize(cpp_lib::type_traits::underlying_cast(in_data), offset, out_archive);
            }

            /* �񋓌^(enum/enum class)�f�V���A���C�Y */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Deserialize(const Archive& in_archive, size_t& offset, T& out_data)
            {
                /* ���̓f�[�^�̊��^�f�[�^ */
                cpp_lib::type_traits::underlying_type_t<T> data{};

                /* ���̓f�[�^�̊��^�Ƃ��ăf�V���A���C�Y */
                this->Deserialize(in_archive, offset, data);

                /* ���̓f�[�^�̌^�ɃL���X�g���ăZ�b�g */
                out_data = static_cast<T>(data);
            }


            /* std::array�^�f�[�^�T�C�Y�Z�o */
            template <typename T, size_t N>
            void Calculate(const std::array<T, N>& in_data, size_t& out_size)
            {
                /* �v�f���̌^(size_t�^)�̃f�[�^�T�C�Y�����Z */
                out_size += sizeof(size_t);

                /* �S�v�f�𑖍� */
                for (const auto& item : in_data)
                {
                    /* �e�v�f�̃f�[�^�T�C�Y���Z�o���ĉ��Z */
                    this->Calculate(item, out_size);
                }
            }

            /* std::array�^�V���A���C�Y */
            template <typename T, size_t N>
            void Serialize(const std::array<T, N>& in_data, size_t& offset, Archive& out_archive)
            {
                /* �v�f�����V���A���C�Y */
                this->Serialize(in_data.size(), offset, out_archive);

                /* �S�v�f�𑖍� */
                for (const auto& item : in_data)
                {
                    /* �e�v�f���V���A���C�Y */
                    this->Serialize(item, offset, out_archive);
                }
            }

            /* std::array�^�f�V���A���C�Y */
            template <typename T, size_t N>
            void Deserialize(const Archive& in_archive, size_t& offset, std::array<T, N>& out_data)
            {
                /* �v�f�� */
                size_t size = 0;

                /* �v�f�����f�V���A���C�Y */
                this->Deserialize(in_archive, offset, size);

                /* �v�f�������[�v */
                for (size_t i = 0; i < size; i++)
                {
                    /* �v�f */
                    T item{};

                    /* �e�v�f���f�V���A���C�Y */
                    this->Deserialize(in_archive, offset, item);

                    /* �v�f���Z�b�g */
                    out_data[i] = item;
                }
            }


            /* std::vector�^�f�[�^�T�C�Y�Z�o */
            template <typename T>
            void Calculate(const std::vector<T>& in_data, size_t& out_size)
            {
                /* �v�f���̌^(size_t�^)�̃f�[�^�T�C�Y�����Z */
                out_size += sizeof(size_t);

                /* �S�v�f�𑖍� */
                for (const auto& item : in_data)
                {
                    /* �e�v�f�̃f�[�^�T�C�Y���Z�o���ĉ��Z */
                    this->Calculate(item, out_size);
                }
            }

            /* std::array�^�V���A���C�Y */
            template <typename T>
            void Serialize(const std::vector<T>& in_data, size_t& offset, Archive& out_archive)
            {
                /* �v�f�����V���A���C�Y */
                this->Serialize(in_data.size(), offset, out_archive);

                /* �S�v�f�𑖍� */
                for (const auto& item : in_data)
                {
                    /* �e�v�f���V���A���C�Y */
                    this->Serialize(item, offset, out_archive);
                }
            }

            /* std::vector�^�f�V���A���C�Y */
            template <typename T>
            void Deserialize(const Archive& in_archive, size_t& offset, std::vector<T>& out_data)
            {
                /* �v�f�� */
                size_t size = 0;

                /* �v�f�����f�V���A���C�Y */
                this->Deserialize(in_archive, offset, size);

                /* �v�f���������������O�m�� */
                out_data.reserve(size);

                /* �v�f�������[�v */
                for (size_t i = 0; i < size; i++)
                {
                    /* �v�f */
                    T item{};

                    /* �e�v�f���f�V���A���C�Y */
                    this->Deserialize(in_archive, offset, item);

                    /* �v�f��ǉ� */
                    out_data.push_back(item);
                }
            }


            /* std::pair�^�f�[�^�T�C�Y�Z�o */
            template <typename T1, typename T2>
            void Calculate(const std::pair<T1, T2>& in_data, size_t& out_size)
            {
                /* 1st�v�f�f�[�^�T�C�Y�Z�o */
                this->Calculate(in_data.first, out_size);

                /* 2nd�v�f�f�[�^�T�C�Y�Z�o */
                this->Calculate(in_data.second, out_size);
            }

            /* std::pair�^�V���A���C�Y */
            template <typename T1, typename T2>
            void Serialize(const std::pair<T1, T2>& in_data, size_t& offset, Archive& out_archive)
            {
                /* 1st�v�f�V���A���C�Y */
                this->Serialize(in_data.first, offset, out_archive);

                /* 2nd�v�f�V���A���C�Y */
                this->Serialize(in_data.second, offset, out_archive);
            }

            /* std::pair�^�f�V���A���C�Y */
            template <typename T1, typename T2>
            void Deserialize(const Archive& in_archive, size_t& offset, std::pair<T1, T2>& out_data)
            {
                /* 1st�v�f */
                T1 first{};

                /* 1st�v�f�f�V���A���C�Y */
                this->Deserialize(in_archive, offset, first);

                /* 2nd�v�f */
                T2 second{};

                /* 2nd�v�f�f�V���A���C�Y */
                this->Deserialize(in_archive, offset, second);

                /* std::pair�ɕϊ����ăZ�b�g */
                out_data = std::make_pair<T1, T2>(first, second);
            }


            /* std::map�^�f�[�^�T�C�Y�Z�o */
            template <typename TKey, typename TValue>
            void Calculate(const std::map<TKey, TValue>& in_data, size_t& out_size)
            {
                /* �v�f���̌^(size_t�^)�̃f�[�^�T�C�Y�����Z */
                out_size += sizeof(size_t);

                /* �S�v�f�𑖍� */
                for (const auto& item : in_data)
                {
                    /* �e�v�f�̃f�[�^�T�C�Y���Z�o���ĉ��Z */
                    this->Calculate(item, out_size);
                }
            }

            /* std::map�^�V���A���C�Y */
            template <typename TKey, typename TValue>
            void Serialize(const std::map<TKey, TValue>& in_data, size_t& offset, Archive& out_archive)
            {
                /* �v�f�����V���A���C�Y */
                this->Serialize(in_data.size(), offset, out_archive);

                /* �S�v�f�𑖍� */
                for (const auto& item : in_data)
                {
                    /* �e�v�f���V���A���C�Y */
                    this->Serialize(item, offset, out_archive);
                }
            }

            /* std::map�^�f�V���A���C�Y */
            template <typename TKey, typename TValue>
            void Deserialize(const Archive& in_archive, size_t& offset, std::map<TKey, TValue>& out_data)
            {
                /* �v�f�� */
                size_t size = 0;

                /* �v�f�����f�V���A���C�Y */
                this->Deserialize(in_archive, offset, size);

                /* �v�f�������[�v */
                for (size_t i = 0; i < size; i++)
                {
                    /* �L�[�v�f */
                    TKey key{};

                    /* �L�[�v�f���f�V���A���C�Y */
                    this->Deserialize(in_archive, offset, key);

                    /* �l�v�f */
                    TValue value{};

                    /* �l�v�f���f�V���A���C�Y */
                    this->Deserialize(in_archive, offset, value);

                    /* �L�[/�l��ǉ� */
                    out_data.emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(value));
                }
            }


            /* �N���X/�\����(class/struct)�^�����o�f�[�^�T�C�Y�Z�o */
            template <typename TUPLE, size_t ...I>
            void CalculateTupleImple(size_t& out_size, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallow�C�f�B�I���ŃN���X/�\����(class/struct)�^�����o�̃^�v���������W�J���A�f�[�^�T�C�Y�Z�o */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Calculate(std::get<I>(t), out_size)), 0)...
                };
            }

            /* �N���X/�\����(class/struct)�^�����o�V���A���C�Y */
            template <typename TUPLE, size_t ...I>
            void SerializeTupleImple(size_t& offset, Archive& out_archive, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallow�C�f�B�I���ŃN���X/�\����(class/struct)�^�����o�̃^�v���������W�J���A�V���A���C�Y */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Serialize(std::get<I>(t), offset, out_archive)), 0)...
                };
            }

            /* �N���X/�\����(class/struct)�^�����o�f�V���A���C�Y */
            template <typename TUPLE, size_t ...I>
            void DeserializeTupleImple(const Archive& in_archive, size_t& offset, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallow�C�f�B�I���ŃN���X/�\����(class/struct)�^�����o�̃^�v���������W�J���A�f�V���A���C�Y */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Deserialize(in_archive, offset, std::get<I>(t))), 0)...
                };
            }


            /* �N���X/�\����(class/struct)�^�����o�^�v���f�[�^�T�C�Y�Z�o */
            template <typename TUPLE>
            void CalculateTuple(size_t& out_size, TUPLE&& t)
            {
                /* �N���X/�\����(class/struct)�^�����o�f�[�^�T�C�Y�Z�o */
                this->CalculateTupleImple(out_size, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* �N���X/�\����(class/struct)�^�����o�^�v���V���A���C�Y */
            template <typename TUPLE>
            void SerializeTuple(size_t& offset, Archive& out_archive, TUPLE&& t)
            {
                /* �N���X/�\����(class/struct)�^�����o�V���A���C�Y */
                this->SerializeTupleImple(offset, out_archive, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* �N���X/�\����(class/struct)�^�����o�^�v���f�V���A���C�Y */
            template <typename TUPLE>
            void DeserializeTuple(const Archive& in_archive, size_t& offset, TUPLE&& t)
            {
                /* �N���X/�\����(class/struct)�^�����o�f�V���A���C�Y */
                this->DeserializeTupleImple(in_archive, offset, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* �N���X/�\����(class/struct)�^�f�[�^�T�C�Y�Z�o */
            template<class T>
            void Calculate(const T& in_data, size_t& out_size, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* �����o�̃^�v���擾 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(in_data);

                /* �����o�̃^�v������e�����o�̃f�[�^�T�C�Y�Z�o */
                this->CalculateTuple(out_size, tuple);
            }

            /* �N���X/�\����(class/struct)�^�V���A���C�Y */
            template <class T>
            void Serialize(const T& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* �����o�̃^�v���擾 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(in_data);

                /* �����o�̃^�v������e�����o���V���A���C�Y */
                this->SerializeTuple(offset, out_archive, tuple);
            }

            /* �N���X/�\����(class/struct)�^�f�V���A���C�Y */
            template <class T>
            void Deserialize(const Archive& in_archive, size_t& offset, T& out_data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* �����o�̃^�v���擾 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(out_data);

                /* �����o�̃^�v������e�����o���f�V���A���C�Y */
                this->DeserializeTuple(in_archive, offset, tuple);
            }


            /* ������^�f�[�^�T�C�Y�Z�o */
            inline void Calculate(const string_t& in_data, size_t& out_size)
            {
                /* �v�f���̌^(size_t�^)�̃f�[�^�T�C�Y�����Z */
                out_size += sizeof(size_t);

                /* �v�f���Z�o(������̒��� + null�����̃T�C�Y) */
                size_t data_size = (in_data.size() + sizeof(char));

                /* �v�f�������Z */
                out_size += data_size;
            }

            /* ������^�V���A���C�Y */
            inline void Serialize(const string_t& in_data, size_t& offset, Archive& out_archive)
            {
                /* �v�f���Z�o(������̒��� + null�����̃T�C�Y) */
                size_t data_size = (in_data.size() + sizeof(char));

                /* �v�f�����V���A���C�Y */
                this->Serialize(data_size, offset, out_archive);

                /* �w��I�t�Z�b�g�ʒu���當����f�[�^�������� */
                out_archive.Write(in_data, offset);
            }

            /* ������^�f�V���A���C�Y */
            inline void Deserialize(const Archive& in_archive, size_t& offset, string_t& out_data)
            {
                /* �v�f�� */
                size_t data_size = 0;

                /* �v�f�����f�V���A���C�Y */
                this->Deserialize(in_archive, offset, data_size);

                /* �w��I�t�Z�b�g�ʒu����w��T�C�Y��������f�[�^�ǂݍ��� */
                in_archive.Read(out_data, offset, data_size);
            }

        private:
            /* ���݂̊��̃G���f�B�A�� */
            cpp_lib::endian::EndianType m_CurrentEndian;

            /* �V���A���C�Y��̃G���f�B�A�� */
            cpp_lib::endian::EndianType m_TargetEndian;
        };
    }
}
