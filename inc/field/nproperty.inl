#pragma once

#include "nproperty.h"
#include "../core/nregistrar.h"

namespace ntr
{

template <typename T, typename ClassT>
NTR_INLINE nproperty::nproperty(ntype* parent_type, std::string_view name, T(ClassT::*member))
    : nproperty(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not property's class type");
    _property_type = nregistrar::get_type<T>();
    _getter = [member](const nreference& instance) -> nobject
    {
        return nobject(instance.cref<ClassT>().*member);
    };
    _setter = [member](const nreference& instance, const nreference& value)
    {
        instance.ref<ClassT>().*member = value.cref<T>();
    };
}

template <typename T, typename ClassT>
NTR_INLINE nproperty::nproperty(ntype* parent_type, std::string_view name,
                            T (ClassT::*getter)() const, void (ClassT::*setter)(const T&))
    : nproperty(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not property's class type");
    _property_type = nregistrar::get_type<T>();
    _getter = [getter](const nreference& instance) -> nobject
    {
        return nobject((instance.cref<ClassT>().*getter)());
    };
    _setter = [setter](const nreference& instance, const nreference& value)
    {
        (instance.ref<ClassT>().*setter)(value.cref<T>());
    };
}

} // namespace ntr