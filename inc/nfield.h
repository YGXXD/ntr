#pragma once

#include "ntype.h"

namespace ntr
{

enum class efield
{
    emember,
    estatic,
};

struct nfield
{
    nfield(ntype* owner_type, efield field_kind, std::string_view name)
        : _owner_type(owner_type), _field_kind(field_kind), _name(name)
    {
    }

    inline ntype* owner_type() const { return _owner_type; }
    inline efield field_kind() const { return _field_kind; }
    inline std::string_view name() const { return _name; }

private:
    ntype* _owner_type;
    efield _field_kind;
    std::string _name;
};

} // namespace ntr
