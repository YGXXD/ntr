#pragma once

#include "../../inc/field/nproperty.hpp"
#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T, typename ClassT>
nproperty::nproperty(const ntype* parent_type, std::string_view name, T(ClassT::* member))
    : nproperty(parent_type, name, nregistrar::get_type<T>())
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nproperty::nproperty : parent type is not property's class type");
    _getter = [member](const nwrapper& instance) -> nobject
    {
        return nobject::make_ref(instance.cref<ClassT>().*member);
    };
    _setter = [member](const nwrapper& instance, const nwrapper& value)
    {
        instance.ref<ClassT>().*member = value.cref<T>();
    };
}

template <typename T, typename ClassT>
nproperty::nproperty(const ntype* parent_type, std::string_view name,
                     const T& (ClassT::*getter)() const, void (ClassT::*setter)(const T&))
    : nproperty(parent_type, name, nregistrar::get_type<T>())
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nproperty::nproperty : parent type is not property's class type");
    _getter = [getter](const nwrapper& instance) -> nobject
    {
        return nobject::make_ref((instance.cref<ClassT>().*getter)());
    };
    _setter = [setter](const nwrapper& instance, const nwrapper& value)
    {
        (instance.ref<ClassT>().*setter)(value.cref<T>());
    };
}

} // namespace ntr