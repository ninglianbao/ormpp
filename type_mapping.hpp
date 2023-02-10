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

        inline constexpr auto type_to_name(identity<std::string>) noexcept { return "TEXT"sv; }

        template<class T>
        inline constexpr auto type_to_name(identity<T>) noexcept {
            using U = std::remove_const_t<std::remove_reference_t<T>>;
            if constexpr (std::is_enum_v<U>) {
                return "INTEGER"sv;
            }
            return "TEXT"sv;
        }

        template<size_t N>
        inline constexpr auto type_to_name(identity<std::array<char, N>>) noexcept {
            return "varchar(" + std::to_string(N) + ")";
        }
    }
}

#endif //EXAMPLE1_TYPE_MAPPING_HPP
