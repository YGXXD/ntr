#pragma once

#include "neitem.h"

namespace ntr
{

// construct
template <typename E>
inline neitem::neitem(ntype* parent_type, std::string_view name, E value)
    : nfield(parent_type, efield::eeitem, name), _value(static_cast<long>(value))
{
}

// get
inline long neitem::value() const
{
    return _value;
}

} // namespace ntr