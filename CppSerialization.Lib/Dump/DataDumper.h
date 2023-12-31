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
        /* データダンプクラス */
        class DataDumper
        {
        public:
            /* 任意の型のデータをダンプして文字列ストリームに追加 */
            template <typename T>
            static void Dump(const T& data, std::stringstream& ss)
            {
                size_t depth = 0;

                DataDumper::Dump(data, depth, ss);
            }

            /* 任意の型のデータをダンプして文字列に変換 */
            template <typename T>
            static std::string ToString(const T& data)
            {
                std::stringstream ss;

                size_t depth = 0;

                DataDumper::Dump(data, depth, ss);

                return ss.str();
            }

            /* 任意の型のデータをダンプして文字列に変換(名前付き) */
            template <typename T>
            static std::string ToString(const std::string name, const T& data)
            {
                std::stringstream ss;

                size_t depth = 0;

                DataDumper::Dump(name, data, depth, ss);

                return ss.str();
            }

            /* 任意の型のデータをダンプしてファイルに出力(追加有無指定可能) */
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

            /* 任意の型のデータをダンプしてファイルに出力(追加有無指定可能、名前付き) */
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

            /* 任意の型のデータをダンプしてファイルストリームに追加 */
            template <typename T>
            static void Dump(const T& data, std::ofstream& file_out)
            {
                std::stringstream ss;

                DataDumper::Dump(data, ss);

                file_out << ss.str() << std::endl;

                file_out << "---" << std::endl;
            }

            /* 任意の型のデータをダンプしてファイルストリームに追加(名前付き) */
            template <typename T>
            static void Dump(const std::string& name, const T& data, std::ofstream& file_out)
            {
                std::stringstream ss;

                DataDumper::Dump(name, data, ss);

                file_out << ss.str() << std::endl;

                file_out << "---" << std::endl;
            }

        private:
            /* 算術型(列挙型以外)ダンプ(インデント付き) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, DataDumper::GetString(data)) << std::endl;
            }

            /* 算術型(列挙型以外)ダンプ(インデント&名前付き) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const std::string& name, const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, DataDumper::GetString(data)) << std::endl;
            }


            /* 列挙(enum/enum class)型ダンプ(インデント付き) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            static void Dump(const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data))) << std::endl;
            }

            /* 列挙(enum/enum class)型ダンプ(インデント&名前付き) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            static void Dump(const std::string& name, const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, DataDumper::GetString(cpp_lib::type_traits::underlying_cast<T>(data))) << std::endl;
            }


            /* クラス/構造体(class/struct)メンバタプル型ダンプ(インデント付き)メンバ展開 */
            template <typename TUPLE, size_t ...I>
            static void DumpTupleImple(const size_t depth, std::stringstream& ss, TUPLE&& t, std::index_sequence<I...>)
            {
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(DataDumper::Dump(std::get<0>(std::get<I>(t)), std::get<1>(std::get<I>(t)), depth + 1, ss)), 0)...
                };
            }

            /* クラス/構造体(class/struct)メンバタプル型ダンプ(インデント付き) */
            template <typename TUPLE>
            static void DumpTuple(const size_t depth, std::stringstream& ss, TUPLE&& t)
            {
                DataDumper::DumpTupleImple(depth, ss, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }


            /* クラス/構造体(class/struct)型ダンプ(インデント付き) */
            template<typename T>
            static void Dump(const T& data, const size_t depth, std::stringstream& ss, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* メンバの名前付きタプル取得 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetNamedMembersAsTuple(data);

                /* メンバの名前付きタプルをダンプ */
                DataDumper::DumpTuple(depth, ss, tuple);
            }

            /* クラス/構造体(class/struct)型ダンプ(インデント&名前付き) */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_class<T>::value> = nullptr>
            static void Dump(const std::string& name, const T& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                DataDumper::Dump(data, depth, ss);
            }


            /* 算術型/列挙型以外のstd::array型ダンプ(インデント付き) */
            template<typename T, size_t N, cpp_lib::type_traits::concept_t<!std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const std::array<T, N>& data, const size_t depth, std::stringstream& ss)
            {
                for (size_t i = 0; i < data.size(); i++)
                {
                    DataDumper::Dump(STRING_FORMAT("[%d]", i), data[i], depth + 1, ss);
                }
            }

            /* 列挙型のstd::array型ダンプ(インデント付き) */
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

            /* 算術型のstd::array型ダンプ(インデント付き) */
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

            /* std::array型ダンプ(インデント&名前付き) */
            template <typename T, size_t N>
            static void Dump(const std::string& name, const std::array<T, N>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                DataDumper::Dump(data, depth, ss);
            }


            /* 算術型/列挙型以外のstd::vector型ダンプ(インデント付き) */
            template<typename T, cpp_lib::type_traits::concept_t<!std::is_arithmetic<T>::value && !std::is_enum<T>::value> = nullptr>
            static void Dump(const std::vector<T>& data, const size_t depth, std::stringstream& ss)
            {
                for (size_t i = 0; i < data.size(); i++)
                {
                    DataDumper::Dump(STRING_FORMAT("[%d]", i), data[i], depth + 1, ss);
                }
            }

            /* 列挙型のstd::vector型ダンプ(インデント付き) */
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

            /* 算術型のstd::vector型ダンプ(インデント付き) */
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

            /* std::vector型ダンプ(インデント&名前付き) */
            template <typename T>
            static void Dump(const std::string& name, const std::vector<T>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                DataDumper::Dump(data, depth, ss);
            }


            /* std::pair型ダンプ(インデント付き) */
            template <typename T1, typename T2>
            static void Dump(const std::pair<T1, T2>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                size_t i = 0;

                DataDumper::Dump("first", data.first, depth + 1, ss);
                DataDumper::Dump("second", data.second, depth + 1, ss);
            }

            /* std::pair型ダンプ(インデント&名前付き) */
            template <typename T1, typename T2>
            static void Dump(const std::string& name, const std::pair<T1, T2>& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, name) << std::endl;

                size_t i = 0;

                DataDumper::Dump("first", data.first, depth + 1, ss);
                DataDumper::Dump("second", data.second, depth + 1, ss);
            }


            /* std::map型ダンプ(インデント付き) */
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

            /* std::map型ダンプ(インデント&名前付き) */
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


            /* 文字列型ダンプ(インデント付き) */
            static inline void Dump(const std::string& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, data) << std::endl;
            }

            /* 文字列型ダンプ(インデント&名前付き) */
            static inline void Dump(const std::string& name, const std::string& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, data) << std::endl;
            }


            /* C形式文字列型ダンプ(インデント付き) */
            static inline void Dump(const char*& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s", indent, data) << std::endl;
            }

            /* C形式文字列型ダンプ(インデント&名前付き) */
            static inline void Dump(const std::string& name, const char*& data, const size_t depth, std::stringstream& ss)
            {
                std::string indent = DataDumper::GetIndent(depth);

                ss << STRING_FORMAT("%s- %s : %s", indent, name, data) << std::endl;
            }

        private:
            /* 算術型(1byteのもの以外)文字列変換 */
            template<typename T, cpp_lib::type_traits::concept_t<cpp_lib::type_traits::is_non_1byte_arithmetic<T>::value> = nullptr>
            static std::string GetString(const T& data)
            {
                return std::to_string(data);
            }

            /* bool型文字列変換 */
            static inline std::string GetString(const bool& data)
            {
                /* bool型はtrue/falseを文字列に変換 */
                return (data == false) ? "false" : "true";
            }

            /* 符号付整数(8bit)型文字列変換 */
            static inline std::string GetString(const int8_t& data)
            {
                /* 8bit整数型は文字(char)とみなされてしまうため、32bit整数として文字列に変換 */
                return std::to_string(static_cast<int32_t>(data));
            }

            /* 符号無整数(8bit)型文字列変換 */
            static inline std::string GetString(const uint8_t& data)
            {
                /* 8bit整数型は文字(char)とみなされてしまうため、32bit整数として文字列に変換 */
                return std::to_string(static_cast<uint32_t>(data));
            }


            /* インデント文字列生成 */
            static std::string GetIndent(const size_t depth);

        private:
            /* コンテナ型の1行に出力する要素数 */
            static const int ContainerValuesSingleLineNum;
        };
    }
}
