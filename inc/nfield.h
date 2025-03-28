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
    nfield(struct ntype* parent_type, efield kind, std::string_view name)
        : _parent_type(parent_type), _kind(kind), _name(name)
    {
    }

    inline ntype* parent_type() const { return _parent_type; }
    inline efield kind() const { return _kind; }
    inline std::string_view name() const { return _name; }

private:
    ntype* _parent_type;
    efield _kind;
    std::string _name;
};

} // namespace ntr
