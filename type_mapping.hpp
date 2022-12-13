#include <sqlite3.h>
#include <string>
#include <string_view>

using namespace std::string_view_literals;

#ifndef EXAMPLE1_TYPE_MAPPING_HPP
#define EXAMPLE1_TYPE_MAPPING_HPP

namespace ormpp {
    template<class T>
    struct identity {
    };


#define REGISTER_TYPE(Type, Index)                                              \
    inline constexpr int type_to_id(identity<Type>) noexcept { return Index; } \
    inline constexpr auto id_to_type( std::integral_constant<std::size_t, Index > ) noexcept { Type res{}; return res; }

    namespace ormpp_sqlite {
        REGISTER_TYPE(int, SQLITE_INTEGER)

        REGISTER_TYPE(double, SQLITE_FLOAT)

        inline int type_to_id(identity<std::string>) noexcept { return SQLITE_TEXT; }

        inline std::string id_to_type(std::integral_constant<std::size_t, SQLITE_TEXT>) noexcept {
            std::string res{};
            return res;
        }

        inline constexpr auto type_to_name(identity<bool>) noexcept { return "INTEGER"sv; }

        inline constexpr auto type_to_name(identity<char>) noexcept { return "INTEGER"sv; }

        inline constexpr auto type_to_name(identity<short>) noexcept { return "INTEGER"sv; }

        inline constexpr auto type_to_name(identity<int>) noexcept { return "INTEGER"sv; }


        inline constexpr auto type_to_name(identity<float>) noexcept { return "FLOAT"sv; }

        inline constexpr auto type_to_name(identity<double>) noexcept { return "DOUBLE"sv; }

        inline constexpr auto type_to_name(identity<int64_t>) noexcept { return "INTEGER"sv; }

        inline constexpr auto type_to_name(identity<uint8_t>) noexcept { return "INTEGER"sv; }

        inline constexpr auto type_to_name(identity<uint16_t>) noexcept { return "INTEGER"sv; }

        inline constexpr auto type_to_name(identity<uint32_t>) noexcept { return "INTEGER"sv; }

        inline constexpr auto type_to_name(identity<uint64_t>) noexcept { return "INTEGER"sv; }

        inline auto type_to_name(identity<std::string>) noexcept { return "TEXT"sv; }

        template<class T>
        inline constexpr auto type_to_name(identity<T>) noexcept {
            if constexpr (std::is_convertible_v<T, bool>) {
                return type_to_name(identity<bool>{});
            }
            if constexpr (std::is_convertible_v<T, char>) {
                return type_to_name(identity<char>{});
            }
            if constexpr (std::is_convertible_v<T, short>) {
                return type_to_name(identity<short>{});
            }
            if constexpr (std::is_convertible_v<T, int>) {
                return type_to_name(identity<int>{});
            }
            if constexpr (std::is_convertible_v<T, unsigned int>) {
                return type_to_name(identity<unsigned int>{});
            }
            if constexpr (std::is_convertible_v<T, float>) {
                return type_to_name(identity<float>{});
            }
            if constexpr (std::is_convertible_v<T, double>) {
                return type_to_name(identity<double>{});
            }
            if constexpr (std::is_convertible_v<T, int64_t>) {
                return type_to_name(identity<int64_t>{});
            }
            if constexpr (std::is_convertible_v<T, uint8_t>) {
                return type_to_name(identity<uint8_t>{});
            }
            if constexpr (std::is_convertible_v<T, uint16_t>) {
                return type_to_name(identity<uint16_t>{});
            }
            if constexpr (std::is_convertible_v<T, uint32_t>) {
                return type_to_name(identity<uint32_t>{});
            }
            if constexpr (std::is_convertible_v<T, uint64_t>) {
                return type_to_name(identity<uint64_t>{});
            }

        }

        template<size_t N>
        inline constexpr auto type_to_name(identity<std::array<char, N>>) noexcept {
            return "varchar(" + std::to_string(N) + ")";
        }
    }
}

#endif //EXAMPLE1_TYPE_MAPPING_HPP
