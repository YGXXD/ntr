#pragma once

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
    static constexpr etype to_etype();

    ntype(etype kind, std::string_view name);

    etype kind() const;
    std::string_view name() const;

    const struct nbasic* as_basic() const;
    const struct nenum* as_enum() const;
    const struct nclass* as_class() const;

protected:
    etype _kind;
    std::string _name;
};

} // namespace ntr