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
        /* バイナリ形式シリアライズクラス */
        class BinarySerialization
        {
        public:
            /* シングルトンインスタンス取得 */
            static BinarySerialization& GetInstance()
            {
                static BinarySerialization instance;
                return instance;
            }

        private:
            /* コンストラクタ */
            BinarySerialization()
                : m_CurrentEndian(cpp_lib::endian::GetEnvironmentEndian())
                , m_TargetEndian(cpp_lib::endian::EndianType::Network)
            {
                /* Nothing to do */
            }

            /* デストラクタ */
            ~BinarySerialization() = default;

        public:
            /* コピー&ムーブセマンティクス無効化 */
            BinarySerialization(const BinarySerialization&) = delete;
            BinarySerialization(BinarySerialization&&) = delete;
            BinarySerialization& operator=(const BinarySerialization&) = delete;
            BinarySerialization& operator=(BinarySerialization&&) = delete;

        public:
            /* シリアライズ後のデータサイズ算出 */
            template <typename T>
            void CalculateSize(const T& in_data, size_t& out_size)
            {
                this->Calculate(in_data, out_size);
            }

            /* 入力データをシリアライズしてアーカイブに変換 */
            template <typename T>
            void Serialize(const T& in_data, serialization::Archive& out_archive)
            {
                /* シリアライズ後のデータサイズ */
                size_t size = 0;

                /* シリアライズ後のデータサイズ算出 */
                this->CalculateSize(in_data, size);

                /* シリアライズ後のデータサイズでアーカイブのデータバッファメモリ確保 */
                out_archive.Reserve(size);

                /* オフセット初期化 */
                size_t offset = 0;

                /* シリアライズ */
                this->Serialize(in_data, offset, out_archive);
            }

            /* アーカイブをデシリアライズして出力データに変換 */
            template <typename T>
            void Deserialize(const serialization::Archive& in_archive, T& out_data)
            {
                /* オフセット初期化 */
                size_t offset = 0;

                /* デシリアライズ */
                this->Deserialize(in_archive, offset, out_data);
            }

        private:
            /* 算術型データサイズ算出 */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            void Calculate(const T& in_data, size_t& out_size)
            {
                /* 入力データの型のサイズを加算 */
                out_size += sizeof(in_data);
            }

            /* 算術型シリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            void Serialize(const T& in_data, size_t& offset, Archive& out_archive)
            {
                /* バイト配列 */
                std::array<byte_t, sizeof(T)> in_bytes{};

                /* 入力データをバイト配列に変換(エンディアンにより必要に応じてスワップ) */
                cpp_lib::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, in_data, in_bytes);

                /* 指定オフセット位置からバイト配列をアーカイブに書き込み */
                out_archive.Write(in_bytes, offset);
            }

            /* 算術型デシリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_arithmetic<T>::value> = nullptr>
            void Deserialize(const Archive& in_archive, size_t& offset, T& out_data)
            {
                /* バイト配列 */
                std::array<byte_t, sizeof(T)> out_bytes{};

                /* アーカイブの指定オフセット位置からバイト配列読み込み */
                in_archive.Read(out_bytes, offset);

                /* バイト配列を出力データに変換(エンディアンにより必要に応じてスワップ) */
                cpp_lib::binary::BinaryConverter::Convert(this->m_CurrentEndian, this->m_TargetEndian, out_bytes, out_data);
            }

            /* 列挙型(enum/enum class)データサイズ算出 */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Calculate(const T& in_data, size_t& out_size)
            {
                /* 入力データの基底型のサイズを加算 */
                this->Calculate(cpp_lib::type_traits::underlying_cast(in_data), out_size);
            }

            /* 列挙型(enum/enum class)シリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Serialize(const T& in_data, size_t& offset, Archive& out_archive)
            {
                /* 入力データの基底型にキャストしてシリアライズ */
                this->Serialize(cpp_lib::type_traits::underlying_cast(in_data), offset, out_archive);
            }

            /* 列挙型(enum/enum class)デシリアライズ */
            template<typename T, cpp_lib::type_traits::concept_t<std::is_enum<T>::value> = nullptr>
            void Deserialize(const Archive& in_archive, size_t& offset, T& out_data)
            {
                /* 入力データの基底型データ */
                cpp_lib::type_traits::underlying_type_t<T> data{};

                /* 入力データの基底型としてデシリアライズ */
                this->Deserialize(in_archive, offset, data);

                /* 入力データの型にキャストしてセット */
                out_data = static_cast<T>(data);
            }


            /* std::array型データサイズ算出 */
            template <typename T, size_t N>
            void Calculate(const std::array<T, N>& in_data, size_t& out_size)
            {
                /* 要素数の型(size_t型)のデータサイズを加算 */
                out_size += sizeof(size_t);

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素のデータサイズを算出して加算 */
                    this->Calculate(item, out_size);
                }
            }

            /* std::array型シリアライズ */
            template <typename T, size_t N>
            void Serialize(const std::array<T, N>& in_data, size_t& offset, Archive& out_archive)
            {
                /* 要素数をシリアライズ */
                this->Serialize(in_data.size(), offset, out_archive);

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素をシリアライズ */
                    this->Serialize(item, offset, out_archive);
                }
            }

            /* std::array型デシリアライズ */
            template <typename T, size_t N>
            void Deserialize(const Archive& in_archive, size_t& offset, std::array<T, N>& out_data)
            {
                /* 要素数 */
                size_t size = 0;

                /* 要素数をデシリアライズ */
                this->Deserialize(in_archive, offset, size);

                /* 要素数分ループ */
                for (size_t i = 0; i < size; i++)
                {
                    /* 要素 */
                    T item{};

                    /* 各要素をデシリアライズ */
                    this->Deserialize(in_archive, offset, item);

                    /* 要素をセット */
                    out_data[i] = item;
                }
            }


            /* std::vector型データサイズ算出 */
            template <typename T>
            void Calculate(const std::vector<T>& in_data, size_t& out_size)
            {
                /* 要素数の型(size_t型)のデータサイズを加算 */
                out_size += sizeof(size_t);

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素のデータサイズを算出して加算 */
                    this->Calculate(item, out_size);
                }
            }

            /* std::array型シリアライズ */
            template <typename T>
            void Serialize(const std::vector<T>& in_data, size_t& offset, Archive& out_archive)
            {
                /* 要素数をシリアライズ */
                this->Serialize(in_data.size(), offset, out_archive);

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素をシリアライズ */
                    this->Serialize(item, offset, out_archive);
                }
            }

            /* std::vector型デシリアライズ */
            template <typename T>
            void Deserialize(const Archive& in_archive, size_t& offset, std::vector<T>& out_data)
            {
                /* 要素数 */
                size_t size = 0;

                /* 要素数をデシリアライズ */
                this->Deserialize(in_archive, offset, size);

                /* 要素数分メモリを事前確保 */
                out_data.reserve(size);

                /* 要素数分ループ */
                for (size_t i = 0; i < size; i++)
                {
                    /* 要素 */
                    T item{};

                    /* 各要素をデシリアライズ */
                    this->Deserialize(in_archive, offset, item);

                    /* 要素を追加 */
                    out_data.push_back(item);
                }
            }


            /* std::pair型データサイズ算出 */
            template <typename T1, typename T2>
            void Calculate(const std::pair<T1, T2>& in_data, size_t& out_size)
            {
                /* 1st要素データサイズ算出 */
                this->Calculate(in_data.first, out_size);

                /* 2nd要素データサイズ算出 */
                this->Calculate(in_data.second, out_size);
            }

            /* std::pair型シリアライズ */
            template <typename T1, typename T2>
            void Serialize(const std::pair<T1, T2>& in_data, size_t& offset, Archive& out_archive)
            {
                /* 1st要素シリアライズ */
                this->Serialize(in_data.first, offset, out_archive);

                /* 2nd要素シリアライズ */
                this->Serialize(in_data.second, offset, out_archive);
            }

            /* std::pair型デシリアライズ */
            template <typename T1, typename T2>
            void Deserialize(const Archive& in_archive, size_t& offset, std::pair<T1, T2>& out_data)
            {
                /* 1st要素 */
                T1 first{};

                /* 1st要素デシリアライズ */
                this->Deserialize(in_archive, offset, first);

                /* 2nd要素 */
                T2 second{};

                /* 2nd要素デシリアライズ */
                this->Deserialize(in_archive, offset, second);

                /* std::pairに変換してセット */
                out_data = std::make_pair<T1, T2>(first, second);
            }


            /* std::map型データサイズ算出 */
            template <typename TKey, typename TValue>
            void Calculate(const std::map<TKey, TValue>& in_data, size_t& out_size)
            {
                /* 要素数の型(size_t型)のデータサイズを加算 */
                out_size += sizeof(size_t);

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素のデータサイズを算出して加算 */
                    this->Calculate(item, out_size);
                }
            }

            /* std::map型シリアライズ */
            template <typename TKey, typename TValue>
            void Serialize(const std::map<TKey, TValue>& in_data, size_t& offset, Archive& out_archive)
            {
                /* 要素数をシリアライズ */
                this->Serialize(in_data.size(), offset, out_archive);

                /* 全要素を走査 */
                for (const auto& item : in_data)
                {
                    /* 各要素をシリアライズ */
                    this->Serialize(item, offset, out_archive);
                }
            }

            /* std::map型デシリアライズ */
            template <typename TKey, typename TValue>
            void Deserialize(const Archive& in_archive, size_t& offset, std::map<TKey, TValue>& out_data)
            {
                /* 要素数 */
                size_t size = 0;

                /* 要素数をデシリアライズ */
                this->Deserialize(in_archive, offset, size);

                /* 要素数分ループ */
                for (size_t i = 0; i < size; i++)
                {
                    /* キー要素 */
                    TKey key{};

                    /* キー要素をデシリアライズ */
                    this->Deserialize(in_archive, offset, key);

                    /* 値要素 */
                    TValue value{};

                    /* 値要素をデシリアライズ */
                    this->Deserialize(in_archive, offset, value);

                    /* キー/値を追加 */
                    out_data.emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(value));
                }
            }


            /* クラス/構造体(class/struct)型メンバデータサイズ算出 */
            template <typename TUPLE, size_t ...I>
            void CalculateTupleImple(size_t& out_size, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallowイディオムでクラス/構造体(class/struct)型メンバのタプルを順次展開し、データサイズ算出 */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Calculate(std::get<I>(t), out_size)), 0)...
                };
            }

            /* クラス/構造体(class/struct)型メンバシリアライズ */
            template <typename TUPLE, size_t ...I>
            void SerializeTupleImple(size_t& offset, Archive& out_archive, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallowイディオムでクラス/構造体(class/struct)型メンバのタプルを順次展開し、シリアライズ */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Serialize(std::get<I>(t), offset, out_archive)), 0)...
                };
            }

            /* クラス/構造体(class/struct)型メンバデシリアライズ */
            template <typename TUPLE, size_t ...I>
            void DeserializeTupleImple(const Archive& in_archive, size_t& offset, TUPLE&& t, std::index_sequence<I...>)
            {
                /* swallowイディオムでクラス/構造体(class/struct)型メンバのタプルを順次展開し、デシリアライズ */
                using swallow = std::initializer_list<int>;

                (void)swallow
                {
                    (void(this->Deserialize(in_archive, offset, std::get<I>(t))), 0)...
                };
            }


            /* クラス/構造体(class/struct)型メンバタプルデータサイズ算出 */
            template <typename TUPLE>
            void CalculateTuple(size_t& out_size, TUPLE&& t)
            {
                /* クラス/構造体(class/struct)型メンバデータサイズ算出 */
                this->CalculateTupleImple(out_size, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* クラス/構造体(class/struct)型メンバタプルシリアライズ */
            template <typename TUPLE>
            void SerializeTuple(size_t& offset, Archive& out_archive, TUPLE&& t)
            {
                /* クラス/構造体(class/struct)型メンバシリアライズ */
                this->SerializeTupleImple(offset, out_archive, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* クラス/構造体(class/struct)型メンバタプルデシリアライズ */
            template <typename TUPLE>
            void DeserializeTuple(const Archive& in_archive, size_t& offset, TUPLE&& t)
            {
                /* クラス/構造体(class/struct)型メンバデシリアライズ */
                this->DeserializeTupleImple(in_archive, offset, std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::decay_t<TUPLE>>::value>{});
            }

            /* クラス/構造体(class/struct)型データサイズ算出 */
            template<class T>
            void Calculate(const T& in_data, size_t& out_size, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* メンバのタプル取得 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(in_data);

                /* メンバのタプルから各メンバのデータサイズ算出 */
                this->CalculateTuple(out_size, tuple);
            }

            /* クラス/構造体(class/struct)型シリアライズ */
            template <class T>
            void Serialize(const T& in_data, size_t& offset, serialization::Archive& out_archive, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* メンバのタプル取得 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(in_data);

                /* メンバのタプルから各メンバをシリアライズ */
                this->SerializeTuple(offset, out_archive, tuple);
            }

            /* クラス/構造体(class/struct)型デシリアライズ */
            template <class T>
            void Deserialize(const Archive& in_archive, size_t& offset, T& out_data, typename std::enable_if<std::is_class<T>::value>::type* = nullptr)
            {
                /* メンバのタプル取得 */
                auto tuple = cpp_lib::type_traits::DataTypeTraits<T>::GetMembersAsTuple(out_data);

                /* メンバのタプルから各メンバをデシリアライズ */
                this->DeserializeTuple(in_archive, offset, tuple);
            }


            /* 文字列型データサイズ算出 */
            inline void Calculate(const string_t& in_data, size_t& out_size)
            {
                /* 要素数の型(size_t型)のデータサイズを加算 */
                out_size += sizeof(size_t);

                /* 要素数算出(文字列の長さ + null文字のサイズ) */
                size_t data_size = (in_data.size() + sizeof(char));

                /* 要素数を加算 */
                out_size += data_size;
            }

            /* 文字列型シリアライズ */
            inline void Serialize(const string_t& in_data, size_t& offset, Archive& out_archive)
            {
                /* 要素数算出(文字列の長さ + null文字のサイズ) */
                size_t data_size = (in_data.size() + sizeof(char));

                /* 要素数をシリアライズ */
                this->Serialize(data_size, offset, out_archive);

                /* 指定オフセット位置から文字列データ書き込み */
                out_archive.Write(in_data, offset);
            }

            /* 文字列型デシリアライズ */
            inline void Deserialize(const Archive& in_archive, size_t& offset, string_t& out_data)
            {
                /* 要素数 */
                size_t data_size = 0;

                /* 要素数をデシリアライズ */
                this->Deserialize(in_archive, offset, data_size);

                /* 指定オフセット位置から指定サイズ分文字列データ読み込み */
                in_archive.Read(out_data, offset, data_size);
            }

        private:
            /* 現在の環境のエンディアン */
            cpp_lib::endian::EndianType m_CurrentEndian;

            /* シリアライズ後のエンディアン */
            cpp_lib::endian::EndianType m_TargetEndian;
        };
    }
}
