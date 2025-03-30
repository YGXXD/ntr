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
    nfield(struct ntype* parent_type, efield kind, std::string_view name);

    inline const ntype* parent_type() const;
    inline const efield kind() const;
    inline const std::string_view name() const;

private:
    ntype* _parent_type;
    efield _kind;
    std::string _name;
};

} // namespace ntr
