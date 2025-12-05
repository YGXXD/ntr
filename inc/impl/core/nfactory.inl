//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/nfactory.hpp"
#include "../../core/nregistrar.hpp"
#include "../../field/neitem.hpp"
#include "../../field/nfunction.hpp"
#include "../../field/nproperty.hpp"

namespace ntr
{

// ntype::etype::eunknown impl
template <typename T>
nfactory<ntype::etype::eunknown, T>::nfactory()
    : _type(ntype::etype::eunknown, static_cast<uint16_t>(sizeof(T)),
            static_cast<uint16_t>(alignof(T)), &ntype_ops_traits<T>::instance().ops, "")
{
}

// ntype::etype::enumeric impl
template <typename T>
nfactory<ntype::etype::enumeric, T>::nfactory()
    : _type(make_enumeric<T>(), static_cast<uint16_t>(sizeof(T)),
            static_cast<uint16_t>(alignof(T)), &ntype_ops_traits<T>::instance().ops, "")
{
}

// ntype::etype::eenum impl
template <typename T>
nfactory<ntype::etype::eenum, T>::nfactory()
    : _type(static_cast<uint16_t>(sizeof(T)), static_cast<uint16_t>(alignof(T)),
            &ntype_ops_traits<T>::instance().ops, "")
{
}

template <typename T>
NTR_INLINE nfactory<ntype::etype::eenum, T>&
nfactory<ntype::etype::eenum, T>::item(std::string_view name, T value)
{
    _type.add_eitem(std::make_unique<neitem>(&_type, name, static_cast<long>(value)));
    return *this;
}

template <typename T>
NTR_INLINE nfactory<ntype::etype::eenum, T>&
nfactory<ntype::etype::eenum, T>::remove(std::string_view name)
{
    _type.remove_eitem(name);
    return *this;
}

// ntype::etype::eclass impl
template <typename T>
nfactory<ntype::etype::eclass, T>::nfactory()
    : _type(static_cast<uint16_t>(sizeof(T)), static_cast<uint16_t>(alignof(T)),
            &ntype_ops_traits<T>::instance().ops, "")
{
}

template <typename T>
template <typename U, typename>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::base_type()
{
    _type.add_base_type(
        nregistrar::get_type<U>(),
        reinterpret_cast<ptrdiff_t>(static_cast<U*>(reinterpret_cast<T*>(1))) - 1);
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name, Ret (*fun)(Args...))
{
    _type.add_function(std::make_unique<nfunction>(&_type, name, fun));
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name, Ret (T::*fun)(Args...))
{
    _type.add_function(std::make_unique<nfunction>(&_type, name, fun));
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name,
                                            Ret (T::*fun)(Args...) const)
{
    _type.add_function(std::make_unique<nfunction>(&_type, name, fun));
    return *this;
}

template <typename T>
template <typename U>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::property(std::string_view name, U(T::* member))
{
    _type.add_property(std::make_unique<nproperty>(&_type, name, member));
    return *this;
}

template <typename T>
template <typename U>
NTR_INLINE nfactory<ntype::etype::eclass, T>& nfactory<ntype::etype::eclass, T>::property(
    std::string_view name, const U& (T::*getter)() const, void (T::*setter)(const U&))
{
    _type.add_property(std::make_unique<nproperty>(&_type, name, getter, setter));
    return *this;
}

template <typename T>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::remove(std::string_view name)
{
    _type.remove_field(name);
    return *this;
}

// ntype::etype::epointer impl
template <typename T>
nfactory<ntype::etype::epointer, T>::nfactory()
    : _type(make_pointer_depth<T>(), std::is_const_v<std::remove_pointer_t<T>>,
            nregistrar::get_type<std::remove_pointer_t<T>>(),
            &ntype_ops_traits<T>::instance().ops, "")
{
}

} // namespace ntr