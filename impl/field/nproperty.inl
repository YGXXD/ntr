#pragma once

#include "../../inc/field/nproperty.hpp"
#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T, typename ClassT>
nproperty::nproperty(ntype* parent_type, std::string_view name, T(ClassT::* member))
    : nproperty(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nproperty::nproperty : parent type is not property's class type");
    _property_type = nregistrar::get_type<T>();
    _getter = [member](const nwrapper& instance) -> nobject
    {
        return nobject::make(instance.cref<ClassT>().*member);
    };
    _setter = [member](const nwrapper& instance, const nwrapper& value)
    {
        instance.ref<ClassT>().*member = value.cref<T>();
    };
}

template <typename T, typename ClassT>
nproperty::nproperty(ntype* parent_type, std::string_view name,
                     T (ClassT::*getter)() const, void (ClassT::*setter)(const T&))
    : nproperty(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nproperty::nproperty : parent type is not property's class type");
    _property_type = nregistrar::get_type<T>();
    _getter = [getter](const nwrapper& instance) -> nobject
    {
        return nobject::make((instance.cref<ClassT>().*getter)());
    };
    _setter = [setter](const nwrapper& instance, const nwrapper& value)
    {
        (instance.ref<ClassT>().*setter)(value.cref<T>());
    };
}

} // namespace ntr