#pragma once

#include <vector>
#include <string>
#include <string_view>

namespace ntr
{

enum class etype
{
    ebasic,
    eclass,
    eenum,
};

struct ntype
{
    ntype(etype kind, std::string_view name) : _kind(kind), _name(name) {}

    inline etype kind() const { return _kind; }
    inline std::string_view name() const { return _name; }

    virtual std::vector<const struct nfield*> fields() const = 0;
    const struct nbasic* as_basic() const;
    const struct nenum* as_enum() const;
    const struct nclass* as_class() const;

private:
    etype _kind;
    std::string _name;
};

} // namespace ntr