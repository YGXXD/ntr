#pragma once

#include "nfactory.h"
#include "nnumeric.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

// ntype::etype::enumeric impl
template <typename T>
inline nfactory<ntype::etype::enumeric, T>&
nfactory<ntype::etype::enumeric, T>::init(std::string_view name)
{
    if (_type == nullptr)
        _type = std::make_unique<nnumeric>(nnumeric::to_enumeric<T>(), name);
    return *this;
}

// ntype::etype::eenum impl
template <typename T>
inline nfactory<ntype::etype::eenum, T>&
nfactory<ntype::etype::eenum, T>::init(std::string_view name)
{
    if (_type == nullptr)
        _type = std::make_unique<nenum>(name);
    return *this;
}

template <typename T>
inline nfactory<ntype::etype::eenum, T>&
nfactory<ntype::etype::eenum, T>::item(std::string_view name, T value)
{
    _type->add_eitem(name, value);
    return *this;
}

template <typename T>
inline nfactory<ntype::etype::eenum, T>&
nfactory<ntype::etype::eenum, T>::remove(std::string_view name)
{
    _type->remove_eitem(name);
    return *this;
}

// ntype::etype::eclass impl
template <typename T>
inline nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::init(std::string_view name)
{
    if (_type == nullptr)
        _type = std::make_unique<nclass>(name);
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
inline nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name, Ret (*fun)(Args...))
{
    _type->add_function(name, fun);
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
inline nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name, Ret (T::*fun)(Args...))
{
    _type->add_function(name, fun);
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
inline nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name,
                                            Ret (T::*fun)(Args...) const)
{
    _type->add_function(name, fun);
    return *this;
}

template <typename T>
template <typename U>
inline nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::property(std::string_view name, U(T::*member))
{
    _type->add_property(name, member);
    return *this;
}

template <typename T>
template <typename U>
inline nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::property(std::string_view name, U (T::*getter)() const,
                                            void (T::*setter)(const U&))
{
    _type->add_property(name, getter, setter);
    return *this;
}

template <typename T>
inline nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::remove(std::string_view name)
{
    _type->remove(name);
    return *this;
}

} // namespace ntr