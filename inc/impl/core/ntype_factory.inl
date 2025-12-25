//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/ntype_factory.hpp"
#include "../../core/ntype_ops_factory.hpp"
#include "../../core/nfield_factory.hpp"
#include "../../core/ncontainer_ops_factory.hpp"
#include "../../core/nregistrar.hpp"

namespace ntr
{

// ntype::etype::eunknown impl
template <typename T>
ntype_factory<ntype::etype::eunknown, T>::ntype_factory()
    : _type(ntype::etype::eunknown, static_cast<uint16_t>(sizeof(T)),
            static_cast<uint16_t>(alignof(T)), &ntype_ops_factory<T>::instance().ops)
{
}

// ntype::etype::enumeric impl
template <typename T>
ntype_factory<ntype::etype::enumeric, T>::ntype_factory()
    : _type(make_enumeric<T>(), static_cast<uint16_t>(sizeof(T)),
            static_cast<uint16_t>(alignof(T)), &ntype_ops_factory<T>::instance().ops)
{
}

// ntype::etype::eenum impl
template <typename T>
ntype_factory<ntype::etype::eenum, T>::ntype_factory()
    : _type(static_cast<uint16_t>(sizeof(T)), static_cast<uint16_t>(alignof(T)),
            &ntype_ops_factory<T>::instance().ops)
{
}

template <typename T>
NTR_INLINE ntype_factory<ntype::etype::eenum, T>&
ntype_factory<ntype::etype::eenum, T>::item(std::string_view name, T value)
{
    _type.add_eitem(nfield_factory::make_eitem(&_type, name, value));
    return *this;
}

template <typename T>
NTR_INLINE ntype_factory<ntype::etype::eenum, T>&
ntype_factory<ntype::etype::eenum, T>::remove(std::string_view name)
{
    _type.remove_eitem(name);
    return *this;
}

// ntype::etype::eclass impl
template <typename T>
ntype_factory<ntype::etype::eclass, T>::ntype_factory()
    : _type(static_cast<uint16_t>(sizeof(T)), static_cast<uint16_t>(alignof(T)),
            &ntype_ops_factory<T>::instance().ops)
{
}

template <typename T>
template <typename U, typename>
NTR_INLINE ntype_factory<ntype::etype::eclass, T>&
ntype_factory<ntype::etype::eclass, T>::base_type()
{
    _type.add_base_type(
        nregistrar::get_type<U>(),
        reinterpret_cast<ptrdiff_t>(static_cast<U*>(reinterpret_cast<T*>(1))) - 1);
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE ntype_factory<ntype::etype::eclass, T>&
ntype_factory<ntype::etype::eclass, T>::function(std::string_view name,
                                                 Ret (*fun)(Args...))
{
    _type.add_function(nfield_factory::make_function(&_type, name, fun));
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE ntype_factory<ntype::etype::eclass, T>&
ntype_factory<ntype::etype::eclass, T>::function(std::string_view name,
                                                 Ret (T::*fun)(Args...))
{
    _type.add_function(nfield_factory::make_function(&_type, name, fun));
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE ntype_factory<ntype::etype::eclass, T>&
ntype_factory<ntype::etype::eclass, T>::function(std::string_view name,
                                                 Ret (T::*fun)(Args...) const)
{
    _type.add_function(nfield_factory::make_function(&_type, name, fun));
    return *this;
}

template <typename T>
template <typename U>
NTR_INLINE ntype_factory<ntype::etype::eclass, T>&
ntype_factory<ntype::etype::eclass, T>::property(std::string_view name, U(T::* member))
{
    _type.add_property(nfield_factory::make_property(&_type, name, member));
    return *this;
}

template <typename T>
template <typename U>
NTR_INLINE ntype_factory<ntype::etype::eclass, T>&
ntype_factory<ntype::etype::eclass, T>::property(std::string_view name,
                                                 const U& (T::*getter_fun)() const,
                                                 void (T::*setter_fun)(const U&))
{
    _type.add_property(
        nfield_factory::make_property(&_type, name, getter_fun, setter_fun));
    return *this;
}

template <typename T>
NTR_INLINE ntype_factory<ntype::etype::eclass, T>&
ntype_factory<ntype::etype::eclass, T>::remove(std::string_view name)
{
    _type.remove_field(name);
    return *this;
}

// ntype::etype::epointer impl
template <typename T>
ntype_factory<ntype::etype::epointer, T>::ntype_factory()
    : _type(nregistrar::get_type<std::remove_pointer_t<T>>())
{
}

// ntype::etype::econtainer impl
template <typename T>
ntype_factory<ntype::etype::econtainer, T>::ntype_factory()
    : _type(
          []()
{
    if constexpr (is_econtainer_map<T>())
        return nregistrar::get_type<typename T::key_type>();
    else
        return nullptr;
}(), nregistrar::get_type<typename T::value_type>(),
          &ncontainer_ops_factory<T>::instance().ops, static_cast<uint16_t>(sizeof(T)),
          static_cast<uint16_t>(alignof(T)), &ntype_ops_factory<T>::instance().ops)
{
}

} // namespace ntr