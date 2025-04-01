#pragma once

#include <string>
#include <string_view>

namespace ntr
{

enum class efield
{
    eeitem,
    eproperty,
    efunction
};

struct nfield
{
    nfield(const struct ntype* parent_type, efield kind, std::string_view name);

    const ntype* parent_type() const;
    const efield kind() const;
    const std::string_view name() const;

protected:
    const ntype* _parent_type;
    efield _kind;
    std::string _name;
};

} // namespace ntr
