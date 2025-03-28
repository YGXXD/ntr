#pragma once

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

struct nbasic;
struct nenum;
struct nclass;
struct ntype
{
    ntype(etype kind, const std::string& name) : _kind(kind), _name(name) {}
    ntype(etype kind, std::string&& name) : _kind(kind), _name(std::move(name)) {}

    inline etype kind() const { return _kind; }
    inline std::string_view name() const { return _name; }

    const nbasic* as_basic() const;
    const nenum* as_enum() const;
    const nclass* as_class() const;

private:
    etype _kind;
    std::string _name;
};

} // namespace ntr