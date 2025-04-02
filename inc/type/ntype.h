#pragma once

#include <string>
#include <string_view>

namespace ntr
{

struct ntype
{
    enum class etype : uint8_t
    {
        eunknown,
        enumeric,
        eenum,
        eclass,
    };

    template <typename T>
    static constexpr bool is_numeric();

    template <typename T>
    static constexpr bool is_enum();

    template <typename T>
    static constexpr bool is_class();

    template <typename T>
    static constexpr etype to_etype();

    friend struct nephren;

    ntype(etype kind, std::string_view name);

    etype kind() const;
    std::string_view name() const;

    bool is_unknown() const;
    bool is_numeric() const;
    bool is_enum() const;
    bool is_class() const;

    const struct nnumeric* as_numeric() const;
    const struct nenum* as_enum() const;
    const struct nclass* as_class() const;

private:
    etype _kind;
    std::string _name;
};

} // namespace ntr