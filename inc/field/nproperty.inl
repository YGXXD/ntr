#pragma once

#include "nproperty.h"
#include "../core/nregistrar.h"

namespace ntr
{

template <typename T, typename ClassT>
inline nproperty::nproperty(ntype* parent_type, std::string_view name, T(ClassT::*member))
    : nproperty(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not property's class type");
    _property_type = nregistrar::get_type<T>();
}

template <typename T, typename ClassT>
inline nproperty::nproperty(ntype* parent_type, std::string_view name,
                            T (ClassT::*getter)() const, void (ClassT::*setter)(const T&))
    : nproperty(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not property's class type");
    _property_type = nregistrar::get_type<T>();
}

} // namespace ntr