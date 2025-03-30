#pragma once

#include "nproperty.h"

namespace ntr
{

// construct
nproperty::nproperty(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::efunction, name)
{
}

template <typename P>
nproperty::nproperty(ntype* parent_type, std::string_view name, P menmber_object_ptr)
    : nfield(parent_type, efield::efunction, name)
{
}

template <typename GetF, typename SetF>
nproperty::nproperty(ntype* parent_type, std::string_view name, GetF getter, SetF setter)
    : nfield(parent_type, efield::efunction, name)
{
}

// get
inline const ntype* nproperty::property_type() const
{
    return _property_type;
}

} // namespace ntr