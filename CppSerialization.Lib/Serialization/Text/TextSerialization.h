/* ���̓f�[�^�̊��^�ɃL���X�g���ăV���A���C�Y */
#pragma once
#include "CommonTypes.h"
#include "Archive.h"
#include "FloatIntConverter.h"
#include "TypeTraits.h"
#include "AppException.h"
#include "StringFormat.h"

#include <sstream>

#include <boost/property_tree/ptree.hpp>

namespace serialization
{
    /* �e�L�X�g�`���V���A���C�Y�N���X */
    class TextSerialization
    {
    public:
        /* �c���[�m�[�h�^ */
        using Node = boost::property_tree::ptree;

    public:
        /* �V���O���g���C���X�^���X�擾 */
        static TextSerialization& GetInstance();

    private:
        /* �R���X�g���N�^ */
        TextSerialization() = default;

        /* �f�X�g���N�^ */
        ~TextSerialization() = default;

    public:
        /* �R�s�[&���[�u�Z�}���e�B�N�X������ */
        TextSerialization(const TextSerialization&) = delete;
        TextSerialization(TextSerialization&&) = delete;
        TextSerialization& operator=(const TextSerialization&) = delete;
        TextSerialization& operator=(TextSerialization&&) = delete;

    public:
        /* ���̓f�[�^���V���A���C�Y���ăA�[�J�C�u�ɕϊ� */
        template <typename T>
        void Serialize(const T& in_data, const string_t& name, serialization::Archive& out_archive)
        {
            /* ���[�g�m�[�h */
            Node root_node{};

            /* �V���A���C�Y */
            this->Serialize(in_data, name, root_node);

            /* �V���A���C�Y�����c���[�m�[�h���e�L�X�g�ɕϊ����A�A�[�J�C�u�ɃZ�b�g */
            this->WriteText(root_node, out_archive);
        }

        /* �A�[�J�C�u���f�V���A���C�Y���ďo�̓f�[�^�ɕϊ� */
        template <typename T>
        void Deserialize(const serialization::Archive& in_archive, const string_t& name, T& out_data)
        {
            /* ���[�g�m�[�h */
            Node root_node{};

            /* �A�[�J�C�u���e�L�X�g�ɕϊ����A�c���[�m�[�h�ɕϊ� */
            this->ReadText(in_archive, root_node);

            /* �f�V���A���C�Y */
            this->Deserialize(root_node, name, out_data);
        }

    private:
        /* bool�ȊO�̐����^�V���A���C�Y */
        template<typename T, util::type_traits::concept_t<util::type_traits::is_nonbool_integral<T>::value> = nullptr>
        void Serialize(const T& in_data, Node& out_node)
        {
            /* �c���[�m�[�h�ɒl��ǉ� */
            out_node.put_value(in_data);
        }

        /* bool�ȊO�̐����^�f�V���A���C�Y */
        template<typename T, util::type_traits::concept_t<util::type_traits::is_nonbool_integral<T>::value> = nullptr>
        void Deserialize(const Node& in_node, T& out_data)
        {
            /* �c���[�m�[�h����v�f�擾 */
            if (auto value = in_node.get_value_optional<T>())
            {
                /* �c���[�m�[�h�v�f����l���擾 */
                out_data = value.get();
            }
            /* �v�f�擾���s���͗�O�n�o */
            else
            {
                THROW_APP_EXCEPTION("Value is nothing");
            }
        }


        /* ���������^�V���A���C�Y */
        template<typename T, util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
        void Serialize(const T& in_data, Node& out_node)
        {
            /* 16�i�������� */
            string_t in_str{};

            /* ���������f�[�^��16�i��������ɕϊ� */
            this->ToHexString(in_data, in_str);

            /* �c���[�m�[�h��16�i��������ɕϊ������l��ǉ� */
            out_node.put_value(in_str);
        }

        /* ���������^�f�V���A���C�Y */
        template<typename T, util::type_traits::concept_t<std::is_floating_point<T>::value> = nullptr>
        void Deserialize(const Node& in_node, T& out_data)
        {
            /* 16�i�������� */
            string_t out_str{};

            /* �c���[�m�[�h����v�f�擾 */
            if (auto value = in_node.get_value_optional<string_t>())
            {
                /* �c���[�m�[�h�v�f����l���擾 */
                out_str = value.get();

                /* �擾�����l(16�i��������)�𕂓������f�[�^�ɕϊ� */
                this->FromHexString(out_str, out_data);
            }
            /* �v�f�擾���s���͗�O�n�o */
            else
            {
                THROW_APP_EXCEPTION("Value is nothing");
            }
        }

        /* �񋓌^(enum/enum class)�V���A���C�Y */
        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        void Serialize(const T& in_data, Node& out_node)
        {
            /* ���̓f�[�^�̊��^�ɃL���X�g���ăV���A���C�Y */
            this->Serialize(util::type_traits::underlying_cast(in_data), out_node);
        }

        /* �񋓌^(enum/enum class)�f�V���A���C�Y */
        template<typename T, util::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
        void Deserialize(const Node& in_node, T& out_data)
        {
            /* ���̓f�[�^�̊��^�f�[�^ */
            util::type_traits::underlying_type_t<T> data{};

            /* ���̓f�[�^�̊��^�Ƃ��ăf�V���A���C�Y */
            this->Deserialize(in_node, data);

            /* ���̓f�[�^�̌^�ɃL���X�g���ăZ�b�g */
            out_data = static_cast<T>(data);
        }

        /* std::array�^�V���A���C�Y */
        template <typename T, size_t N>
        void Serialize(const std::array<T, N>& in_data, const string_t& name, Node& out_node)
        {
            /* ���O���w�肵�Ďq�m�[�h��ǉ� */
            auto& child_node = out_node.add(name, "");

            /* �S�v�f�𑖍� */
            for (const auto& item : in_data)
            {
                /* �e�v�f���V���A���C�Y���Ďq�m�[�h�ɒǉ� */
                this->Serialize(item, "item", child_node);
            }
        }

        /* std::array�^�f�V���A���C�Y */
        template <typename T, size_t N>
        void Deserialize(const Node& in_node, const string_t& name, std::array<T, N>& out_data)
        {
            /* ���O���w�肵�Ďq�m�[�h���擾 */
            auto& child_node = in_node.get_child(name);

            /* �C���f�b�N�X */
            size_t i = 0;

            /* �q�m�[�h�̑S�v�f�𑖍� */
            for (const auto& item_node_pair : child_node)
            {
                /* �v�f */
                T item{};

                /* �e�v�f���f�V���A���C�Y */
                this->Deserialize(item_node_pair.second, item);

                /* �v�f���Z�b�g */
                out_data[i] = item;

                /* �C���f�b�N�X�C���N�������g */
                i++;
            }
        }


        /* std::vector�^�V���A���C�Y */
        template <typename T>
        void Serialize(const std::vector<T>& in_data, const string_t& name, Node& out_node)
        {
            /* ���O���w�肵�Ďq�m�[�h��ǉ� */
            auto& child_node = out_node.add(name, "");

            /* �S�v�f�𑖍� */
            for (const auto& item : in_data)
            {
                /* �e�v�f���V���A���C�Y���Ďq�m�[�h�ɒǉ� */
                this->Serialize(item, "item", child_node);
            }
        }

        /* std::vector�^�f�V���A���C�Y */
        template <typename T>
        void Deserialize(const Node& in_node, const string_t& name, std::vector<T>& out_data)
        {
            /* ���O���w�肵�Ďq�m�[�h���擾 */
            auto& child_node = in_node.get_child(name);

            /* �o�̓f�[�^�N���A */
            out_data.clear();

            /* �q�m�[�h�̗v�f���������������O�m�� */
            out_data.reserve(child_node.size());

            /* �q�m�[�h�̑S�v�f�𑖍� */
            for (const auto& item_node_pair : child_node)
            {
                /* �v�f */
                T item{};

                /* �e�v�f���f�V���A���C�Y */
                this->Deserialize(item_node_pair.second, item);

                /* �v�f��ǉ� */
                out_data.push_back(item);
            }
        }


        /* std::pair�^�V���A���C�Y */
        template <typename T1, typename T2>
        void Serialize(const std::pair<T1, T2>& in_data, Node& out_node)
        {
            /* 1st�v�f�V���A���C�Y */
            this->Serialize(in_data.first, "first", out_node);

            /* 2nd�v�f�V���A���C�Y */
            this->Serialize(in_data.second, "second", out_node);
        }

        /* std::pair�^�f�V���A���C�Y */
        template <typename T1, typename T2>
        void Deserialize(const Node& in_node, std::pair<T1, T2>& out_data)
        {
            /* 1st�v�f */
            T1 first{};

            /* 1st�v�f�f�V���A���C�Y */
            this->Deserialize(in_node, "first", first);

            /* 2nd�v�f */
            T2 second{};

            /* 2nd�v�f�f�V���A���C�Y */
            this->Deserialize(in_node, "second", second);

            /* std::pair�ɕϊ����ăZ�b�g */
            out_data = std::make_pair<T1, T2>(first, second);
        }


        /* std::map�^�V���A���C�Y */
        template <typename TKey, typename TValue>
        void Serialize(const std::map<TKey, TValue>& in_data, const string_t& name, Node& out_node)
        {
            /* ���O���w�肵�Ďq�m�[�h��ǉ� */
            auto& child_node = out_node.add(name, "");

            /* �S�v�f�𑖍� */
            for (const auto& item : in_data)
            {
                /* �e�v�f���V���A���C�Y���Ďq�m�[�h�ɒǉ� */
                this->Serialize(item, "item", child_node);
            }
        }

        template <typename TKey, typename TValue>
        void Deserialize(const Node& in_node, const string_t& name, std::map<TKey, TValue>& out_data)
        {
            /* ���O���w�肵�Ďq�m�[�h���擾 */
            auto& child_node = in_node.get_child(name);

            /* �q�m�[�h�̑S�v�f�𑖍� */
            for (const auto& item_node_pair : child_node)
            {
                /* �L�[�v�f */
                TKey key{};

                /* �L�[�v�f�f�V���A���C�Y */
                this->Deserialize(item_node_pair.second, "first", key);

                /* �l�v�f */
                TValue value{};

                /* �l�v�f�f�V���A���C�Y */
                this->Deserialize(item_node_pair.second, "second", value);

                /* �L�[/�l��ǉ� */
                out_data.emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(value));
            }
        }

        /* �N���X/�\����(class/struct)�^�����o�V���A���C�Y */
        template <typename TUPLE, size_t ...I>
        void SerializeTupleImple(Node& out_node, TUPLE&& t, std::index_sequence<I...>)
        {
            /* swallow�C�f�B�I���ŃN���X/�\����(class/struct)�^�����o�̃^�v���������W�J���A�V���A���C�Y */
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(this->Serialize(std::get<1>(std::get<I>(t)), std::get<0>(std::get<I>(t)), out_node)), 0)...
            };
        }

        /* �N���X/�\����(class/struct)�^�����o�f�V���A���C�Y */
        template <typename TUPLE, size_t ...I>
        void DeserializeTupleImple(const Node& in_node, TUPLE&& t, std::index_sequence<I...>)
        {
            /* swallow�C�f�B�I���ŃN���X/�\����(class/struct)�^�����o�̃^�v���������W�J���A�f�V���A���C�Y */
            using swallow = std::initializer_list<int>;

            (void)swallow
            {
                (void(this->Deserialize(in_node, std::get<0>(std::get<I>(t)), std::get<1>(std::get<I>(t)))), 0)...
            };
        }

        /* �N���X/�\����(class/struct)�^�����o�^�v���V���A���C�Y */
        template <typename TUPLE>
        void SerializeTuple(Node& out_node, TUPLE&& t)
        {
            /* �N���X/�\����(class/struct)�^�����o�V���A���C�Y */
            this->SerializeTupleImple(out_node, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }

        /* �N���X/�\����(class/struct)�^�����o�^�v���f�V���A���C�Y */
        template <typename TUPLE>
        void DeserializeTuple(const Node& in_node, TUPLE&& t)
        {
            /* �N���X/�\����(class/struct)�^�����o�f�V���A���C�Y */
            this->DeserializeTupleImple(in_node, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
        }


        /* �N���X/�\����(class/struct)�^�V���A���C�Y */
        template <class T>
        void Serialize(const T& in_data, Node& out_node, typename std::enable_if<std::is_class<T>::value>::type* = nullptr);

        /* �N���X/�\����(class/struct)�^�f�V���A���C�Y */
        template <class T>
        void Deserialize(const Node& in_node, T& out_data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr);


        /* ���O�t���I�u�W�F�N�g�V���A���C�Y */
        template <typename T>
        void Serialize(const T& in_data, const string_t& name, Node& out_node)
        {
            /* �c���[�m�[�h�ɖ��O���w�肵�Ďq�m�[�h�ǉ� */
            auto& child_node = out_node.add(name, "");

            /* ���̓f�[�^���V���A���C�Y���Ďq�m�[�h�ɒǉ� */
            this->Serialize(in_data, child_node);
        }

        /* ���O�t���I�u�W�F�N�g�f�V���A���C�Y */
        template <typename T>
        void Deserialize(const Node& in_node, const string_t& name, T& out_data)
        {
            /* �c���[�m�[�h�ɖ��O���w�肵�Ďq�m�[�h�擾 */
            auto& child_node = in_node.get_child(name);

            /* �q�m�[�h����f�[�^���f�V���A���C�Y */
            this->Deserialize(child_node, out_data);
        }

    private:
        /* �_���^(bool)�V���A���C�Y */
        void Serialize(const bool_t& in_data, Node& out_node);

        /* �_���^(bool)�f�V���A���C�Y */
        void Deserialize(const Node& in_node, bool_t& out_data);

        /* ������^�V���A���C�Y */
        void Serialize(const string_t& in_data, Node& out_node);

        /* ������^�f�V���A���C�Y */
        void Deserialize(const Node& in_node, string_t& out_data);


        /* �V���A���C�Y�����c���[�m�[�h���e�L�X�g�ɕϊ����A�A�[�J�C�u�ɃZ�b�g */
        void WriteText(const Node& in_root_node, serialization::Archive& out_archive);

        /* �A�[�J�C�u���e�L�X�g�ɕϊ����A�c���[�m�[�h�ɕϊ� */
        void ReadText(const serialization::Archive& in_archive, Node& out_root_node);

        /* ���������f�[�^(32bit)��16�i��������ɕϊ� */
        void ToHexString(const float32_t& in_data, string_t& out_data);

        /* ���������f�[�^(64bit)��16�i��������ɕϊ� */
        void ToHexString(const float64_t& in_data, string_t& out_data);

        /* 16�i��������𕂓�����(32bit)�f�[�^�ɕϊ� */
        void FromHexString(const string_t& in_data, float32_t& out_data);

        /* 16�i��������𕂓�����(64bit)�f�[�^�ɕϊ� */
        void FromHexString(const string_t& in_data, float64_t& out_data);
    };
}
