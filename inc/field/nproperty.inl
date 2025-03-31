#pragma once

#include "nproperty.h"
#include "../nephren.h"

namespace ntr
{

// construct
inline nproperty::nproperty(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::efunction, name)
{
}

template <typename T, typename ClassT>
inline nproperty::nproperty(ntype* parent_type, std::string_view name, T(ClassT::*member))
    : nproperty(parent_type, name)
{
    assert(parent_type == nephren::get_type<ClassT>());
    _property_type = nephren::get_type<std::decay_t<T>>();
    assert(_property_type != nullptr);
}

template <typename T, typename ClassT>
inline nproperty::nproperty(ntype* parent_type, std::string_view name,
                            T (ClassT::*getter)() const, void (ClassT::*setter)(T))
    : nproperty(parent_type, name)
{
    assert(parent_type == nephren::get_type<ClassT>());
    _property_type = nephren::get_type<std::decay_t<T>>();
    assert(_property_type != nullptr);
}

// get
inline const ntype* nproperty::property_type() const
{
    return _property_type;
}

} // namespace ntr