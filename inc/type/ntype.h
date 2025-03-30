#pragma once

#include <type_traits>
#include <string>
#include <string_view>

namespace ntr
{

struct ntype
{

    enum class etype
    {
        ebasic,
        eclass,
        eenum,
    };

    template <typename T>
    static inline constexpr etype to_etype()
    {
        if constexpr (std::is_fundamental_v<T>)
            return etype::ebasic;
        else if constexpr (std::is_enum_v<T>)
            return etype::eenum;
        else if constexpr (std::is_class_v<T>)
            return etype::eclass;
        else
            static_assert(!std::is_same_v<T, T>,
                          "unknown type, to_etype template param \"T\" must be "
                          "fundamental, enum and class");
    }

    ntype(etype kind, std::string_view name) : _kind(kind), _name(name) {}

    inline etype kind() const { return _kind; }
    inline std::string_view name() const { return _name; }

    const struct nbasic* as_basic() const;
    const struct nenum* as_enum() const;
    const struct nclass* as_class() const;

private:
    etype _kind;
    std::string _name;
};

} // namespace ntr