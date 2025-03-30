#pragma once

#include "nfield.h"

namespace ntr
{

// construct
inline nfield::nfield(struct ntype* parent_type, efield kind, std::string_view name)
    : _parent_type(parent_type), _kind(kind), _name(name)
{
}

// get
inline const ntype* nfield::parent_type() const
{
    return _parent_type;
}

inline const efield nfield::kind() const
{
    return _kind;
}

inline const std::string_view nfield::name() const
{
    return _name;
}

} // namespace ntr