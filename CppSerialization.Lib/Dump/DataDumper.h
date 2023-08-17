#pragma once
#include "CommonTypes.h"
#include "TypeTraits.h"
#include "DataTypeTraits.h"
#include "StringFormat.h"

#include <sstream>
#include <fstream>

namespace cpp_lib
{
    namespace dump
    {
        /* �f�[�^�_���v�N���X */
        class DataDumper
        {
        public:
            /* �C�ӂ̌^�̃f�[�^���_���v���ĕ�����X�g���[���ɒǉ� */
            template <typename T>
            static void Dump(const T& data, std::stringstream& ss)
            {
                size_t depth = 0;

                DataDumper::Dump(data, depth, ss);
            }

            /* �C�ӂ̌^�̃f�[�^���_���v���ĕ�����ɕϊ� */
            template <typename T>
            static std::string ToString(const T& data)
            {
                std::stringstream ss;

                size_t depth = 0;

                DataDumper::Dump(data, depth, ss);

                return ss.str();
            }

            /* �C�ӂ̌^�̃f�[�^���_���v���ĕ�����ɕϊ�(���O�t��) */
            template <typename T>
            static std::string ToString(const std::string name, const T& data)
            {
                std::stringstream ss;

                size_t depth = 0;

                DataDumper::Dump(name, data, depth, ss);

                return ss.str();
            }

            /* �C�ӂ̌^�̃f�[�^���_���v���ăt�@�C���ɏo��(�ǉ��L���w��\) */
            template <typename T>
            static void Dump(const T& data, const std::string file_name, bool append)
            {
                std::stringstream ss;

                DataDumper::Dump(data, ss);

                if (append == true)
                {
                    std::ofstream file_out;

                    file_out.open(file_name, std::ios_base::app);

                    file_out << ss.str() << std::endl;

                    file_out << "---" << std::endl;
                }
                else
                {
                    std::ofstream file_out(file_name);

                    file_out << ss.str() << std::endl;

                    file_out << "---" << std::endl;
                }
            }

            /* �C�ӂ̌^�̃f�[�^���_���v���ăt�@�C���ɏo��(�ǉ��L���w��\�A���O�t��) */
            template <typename T>
            static void Dump(const std::string& name, const T& data, const std::string file_name, bool append)
            {
                std::stringstream ss;

                DataDumper::Dump(name, data, ss);

                if (append == true)
                {
                    std::ofstream file_out;

                    file_out.open(file_name, std::ios_base::app);

                    file_out << ss.str() << std::endl;

                    file_out << "---" << std::endl;
                }
                else
                {
                    std::ofstream file_out(file_name);

                    file_out << ss.str() << std::endl;

                    file_out << "---" << std::endl;
                }
            }

            /* �C�ӂ̌^�̃f�[�^���_���v���ăt�@�C���X�g���[���ɒǉ� */
            template <typename T>
            static void Dump(const T& data, std::ofstream& file_out)
            {
                std::stringstream ss;

                DataDumper::Dump(data, ss);

                file_out << ss.str() << std::endl;

                file_out << "---" << std::endl;
            }

            /* �C�ӂ̌^�̃f�[�^���_���v���ăt�@�C���X�g���[���ɒǉ�(���O�t��) */
            template <typename T>
            static void Dump(const std::string& name, const T& data, std::ofstream& file_out)
            {
                std::stringstream ss;

                DataDumper::Dump(name, data, ss);

                file_out << ss.str() << std::endl;

                file_out << "---" << std::endl;
            }

        private:
            /* �Z�p�^(�񋓌^�ȊO)�_���v(�C���f���g�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, DataDumper::GetString(data)) << std::endl;
            }

            /* �Z�p�^(�񋓌^�ȊO)�_���v(�C���f���g&���O�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const std::string& name, const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, DataDumper::GetString(data)) << std::endl;
            }


            /* ��(enum/enum class)�^�_���v(�C���f���g�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            static void Dump(const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data))) << std::endl;
            }

            /* ��(enum/enum class)�^�_���v(�C���f���g&���O�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            static void Dump(const std::string& name, const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data))) << std::endl;
            }


            /* �N���X/�\����(class/struct)�����o�^�v���^�_���v(�C���f���g�t��)�����o�W�J */
            template <typename TUPLE, size_t ...I>
            static void DumpTupleImple(const size_t depth, std::stringstream& ss, TUPLE&& t, std::index_sequence<I...>)
            {
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(DataDumper::Dump(std::get<0>(std::get<I>(t)), std::get<1>(std::get<I>(t)), depth + 1, ss)), 0)...
                };
            }

            /* �N���X/�\����(class/struct)�����o�^�v���^�_���v(�C���f���g�t��) */
            template <typename TUPLE>
            static void DumpTuple(const size_t depth, std::stringstream& ss, TUPLE&& t)
            {
                DataDumper::DumpTupleImple(depth, ss, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }


            /* �N���X/�\����(class/struct)�^�_���v(�C���f���g�t��) */
            template<typename T>
            static void Dump(const T& data, const size_t depth, std::stringstream& ss, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* �����o�̖��O�t���^�v���擾 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetNamedMembersAsTuple(data);

                /* �����o�̖��O�t���^�v�����_���v */
                DataDumper::DumpTuple(depth, ss, tuple);
            }

            /* �N���X/�\����(class/struct)�^�_���v(�C���f���g&���O�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_class<T>::value> = nullptr>
            static void Dump(const std::string& name, const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                DataDumper::Dump(data, depth, ss);
            }


            /* �Z�p�^/�񋓌^�ȊO��std::array�^�_���v(�C���f���g�t��) */
            template<typename T, size_t N, cpp_lib::type_traits::concept_t<!std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const std::array<T, N>& data, const size_t depth, std::stringstream& ss)
            {
                for (size_t i = 0; i < data.size(); i++)
                {
                    DataDumper::Dump(STRING_FORMAT("[%d]", i), data[i], depth + 1, ss);
                }
            }

            /* �񋓌^��std::array�^�_���v(�C���f���g�t��) */
            template<typename T, size_t N, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            static void Dump(const std::array<T, N>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth + 1);

                for (size_t i = 0; i < data.size(); i++)
                {
                    if (i == 0)
                    {
                        ss << indent << DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data[i]));
                    }
                    else
                    {
                        ss << ",";

                        if (i % DataDumper::ContainerValuesSingleLineNum == 0)
                        {
                            ss << std::endl;
                            ss << indent;
                        }
                        else
                        {
                            ss << " ";
                        }

                        ss << DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data[i]));
                    }
                }

                ss << std::endl;
            }

            /* �Z�p�^��std::array�^�_���v(�C���f���g�t��) */
            template<typename T, size_t N, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Dump(const std::array<T, N>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth + 1);

                for (size_t i = 0; i < data.size(); i++)
                {
                    if (i == 0)
                    {
                        ss << indent << DataDumper::GetString(data[i]);
                    }
                    else
                    {
                        ss << ",";

                        if (i % DataDumper::ContainerValuesSingleLineNum == 0)
                        {
                            ss << std::endl;
                            ss << indent;
                        }
                        else
                        {
                            ss << " ";
                        }

                        ss << DataDumper::GetString(data[i]);
                    }
                }

                ss << std::endl;
            }

            /* std::array�^�_���v(�C���f���g&���O�t��) */
            template <typename T, size_t N>
            static void Dump(const std::string& name, const std::array<T, N>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                DataDumper::Dump(data, depth, ss);
            }


            /* �Z�p�^/�񋓌^�ȊO��std::vector�^�_���v(�C���f���g�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<!std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const std::vector<T>& data, const size_t depth, std::stringstream& ss)
            {
                for (size_t i = 0; i < data.size(); i++)
                {
                    DataDumper::Dump(STRING_FORMAT("[%d]", i), data[i], depth + 1, ss);
                }
            }

            /* �񋓌^��std::vector�^�_���v(�C���f���g�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            static void Dump(const std::vector<T>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth + 1);

                for (size_t i = 0; i < data.size(); i++)
                {
                    if (i == 0)
                    {
                        ss << indent << DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data[i]));
                    }
                    else
                    {
                        ss << ",";

                        if (i % DataDumper::ContainerValuesSingleLineNum == 0)
                        {
                            ss << std::endl;
                            ss << indent;
                        }
                        else
                        {
                            ss << " ";
                        }

                        ss << DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data[i]));
                    }
                }

                ss << std::endl;
            }

            /* �Z�p�^��std::vector�^�_���v(�C���f���g�t��) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            static void Dump(const std::vector<T>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth + 1);

                for (size_t i = 0; i < data.size(); i++)
                {
                    if (i == 0)
                    {
                        ss << indent << DataDumper::GetString(data[i]);
                    }
                    else
                    {
                        ss << ",";

                        if (i % DataDumper::ContainerValuesSingleLineNum == 0)
                        {
                            ss << std::endl;
                            ss << indent;
                        }
                        else
                        {
                            ss << " ";
                        }

                        ss << DataDumper::GetString(data[i]);
                    }
                }

                ss << std::endl;
            }

            /* std::vector�^�_���v(�C���f���g&���O�t��) */
            template <typename T>
            static void Dump(const std::string& name, const std::vector<T>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                DataDumper::Dump(data, depth, ss);
            }


            /* std::pair�^�_���v(�C���f���g�t��) */
            template <typename T1, typename T2>
            static void Dump(const std::pair<T1, T2>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                size_t i = 0;

                DataDumper::Dump("first", data.first, depth + 1, ss);
                DataDumper::Dump("second", data.second, depth + 1, ss);
            }

            /* std::pair�^�_���v(�C���f���g&���O�t��) */
            template <typename T1, typename T2>
            static void Dump(const std::string& name, const std::pair<T1, T2>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                size_t i = 0;

                DataDumper::Dump("first", data.first, depth + 1, ss);
                DataDumper::Dump("second", data.second, depth + 1, ss);
            }


            /* std::map�^�_���v(�C���f���g�t��) */
            template <typename T1, typename T2>
            static void Dump(const std::map<T1, T2>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                size_t i = 0;

                for (const auto& item : data)
                {
                    DataDumper::Dump(STRING_FORMAT("[%d]", i), item, depth + 1, ss);
                    i++;
                }
            }

            /* std::map�^�_���v(�C���f���g&���O�t��) */
            template <typename T1, typename T2>
            static void Dump(const std::string& name, const std::map<T1, T2>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                size_t i = 0;

                for (const auto& item : data)
                {
                    DataDumper::Dump(STRING_FORMAT("[%d]", i), item, depth + 1, ss);
                    i++;
                }
            }


            /* ������^�_���v(�C���f���g�t��) */
            static inline void Dump(const std::string& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, data) << std::endl;
            }

            /* ������^�_���v(�C���f���g&���O�t��) */
            static inline void Dump(const std::string& name, const std::string& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, data) << std::endl;
            }


            /* C�`��������^�_���v(�C���f���g�t��) */
            static inline void Dump(const char*& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, data) << std::endl;
            }

            /* C�`��������^�_���v(�C���f���g&���O�t��) */
            static inline void Dump(const std::string& name, const char*& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, data) << std::endl;
            }

        private:
            /* �Z�p�^(1byte�̂��̈ȊO)������ϊ� */
            template<typename T, cpp_lib::type_traits::concept_t<cpp_lib::type_traits::is_non_1byte_arithmetic<T>::value> = nullptr>
            static std::string GetString(const T& data)
            {
                return std::to_string(data);
            }

            /* bool�^������ϊ� */
            static inline std::string GetString(const bool& data)
            {
                /* bool�^��true/false�𕶎���ɕϊ� */
                return (data == false) ? "false" : "true";
            }

            /* �����t����(8bit)�^������ϊ� */
            static inline std::string GetString(const int8_t& data)
            {
                /* 8bit�����^�͕���(char)�Ƃ݂Ȃ���Ă��܂����߁A32bit�����Ƃ��ĕ�����ɕϊ� */
                return std::to_string(static_cast<int32_t>(data));
            }

            /* ����������(8bit)�^������ϊ� */
            static inline std::string GetString(const uint8_t& data)
            {
                /* 8bit�����^�͕���(char)�Ƃ݂Ȃ���Ă��܂����߁A32bit�����Ƃ��ĕ�����ɕϊ� */
                return std::to_string(static_cast<uint32_t>(data));
            }


            /* �C���f���g�����񐶐� */
            static std::string GetIndent(const size_t depth);

        private:
            /* �R���e�i�^��1�s�ɏo�͂���v�f�� */
            static const int ContainerValuesSingleLineNum;
        };
    }
}