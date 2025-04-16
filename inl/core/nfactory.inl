#pragma once

#include "../../inc/core/nfactory.h"
#include "../../inc/type/nnumeric.h"
#include "../../inc/type/nenum.h"
#include "../../inc/type/nclass.h"
#include "../../inc/field/neitem.h"
#include "../../inc/field/nfunction.h"
#include "../../inc/field/nproperty.h"

namespace ntr
{

// ntype::etype::eunknown impl
template <typename T>
NTR_INLINE nfactory<ntype::etype::eunknown, T>::nfactory()
{
    _type = std::make_unique<ntype>(ntype::etype::eunknown, typeid(T).name());
}

// ntype::etype::enumeric impl
template <typename T>
NTR_INLINE nfactory<ntype::etype::enumeric, T>::nfactory()
{
    _type = std::make_unique<nnumeric>(make_enumeric<T>(), typeid(T).name());
}

// ntype::etype::eenum impl
template <typename T>
NTR_INLINE nfactory<ntype::etype::eenum, T>::nfactory()
{
    _type = std::make_unique<nenum>(typeid(T).name());
}

template <typename T>
NTR_INLINE nfactory<ntype::etype::eenum, T>&
nfactory<ntype::etype::eenum, T>::item(std::string_view name, T value)
{
    _type->add_eitem(
        std::make_unique<neitem>(_type.get(), name, static_cast<long>(value)));
    return *this;
}

template <typename T>
NTR_INLINE nfactory<ntype::etype::eenum, T>&
nfactory<ntype::etype::eenum, T>::remove(std::string_view name)
{
    _type->remove_eitem(name);
    return *this;
}

// ntype::etype::eclass impl
template <typename T>
NTR_INLINE nfactory<ntype::etype::eclass, T>::nfactory()
{
    _type = std::make_unique<nclass>(typeid(T).name());
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name, Ret (*fun)(Args...))
{
    _type->add_function(std::make_unique<nfunction>(_type.get(), name, fun));
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name, Ret (T::*fun)(Args...))
{
    _type->add_function(std::make_unique<nfunction>(_type.get(), name, fun));
    return *this;
}

template <typename T>
template <typename Ret, typename... Args>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::function(std::string_view name,
                                            Ret (T::*fun)(Args...) const)
{
    _type->add_function(std::make_unique<nfunction>(_type.get(), name, fun));
    return *this;
}

template <typename T>
template <typename U>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::property(std::string_view name, U(T::*member))
{
    _type->add_property(std::make_unique<nproperty>(_type.get(), name, member));
    return *this;
}

template <typename T>
template <typename U>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::property(std::string_view name, U (T::*getter)() const,
                                            void (T::*setter)(const U&))
{
    _type->add_property(std::make_unique<nproperty>(_type.get(), name, getter, setter));
    return *this;
}

template <typename T>
NTR_INLINE nfactory<ntype::etype::eclass, T>&
nfactory<ntype::etype::eclass, T>::remove(std::string_view name)
{
    _type->remove(name);
    return *this;
}

} // namespace ntr