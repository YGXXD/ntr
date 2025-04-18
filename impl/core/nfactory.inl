#pragma once

#include "../../inc/core/nfactory.hpp"
#include "../../inc/type/nnumeric.hpp"
#include "../../inc/type/nenum.hpp"
#include "../../inc/type/nclass.hpp"
#include "../../inc/field/neitem.hpp"
#include "../../inc/field/nfunction.hpp"
#include "../../inc/field/nproperty.hpp"

namespace ntr
{

// ntype::etype::eunknown impl
template <typename T>
nfactory<ntype::etype::eunknown, T>::nfactory()
{
    constexpr size_t size = []()
    {
        if constexpr (std::is_same_v<T, void>)
            return 0;
        else
            return sizeof(T);
    }();
    _type =
        std::make_unique<ntype>(ntype::etype::eunknown, size,
                                &ntype_ops_traits<T>::instance().ops, typeid(T).name());
}

// ntype::etype::enumeric impl
template <typename T>
nfactory<ntype::etype::enumeric, T>::nfactory()
{
    _type = std::make_unique<nnumeric>(make_enumeric<T>(), sizeof(T),
                                       &ntype_ops_traits<T>::instance().ops,
                                       typeid(T).name());
}

// ntype::etype::eenum impl
template <typename T>
nfactory<ntype::etype::eenum, T>::nfactory()
{
    _type = std::make_unique<nenum>(typeid(T).name(), sizeof(T),
                                    &ntype_ops_traits<T>::instance().ops);
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
nfactory<ntype::etype::eclass, T>::nfactory()
{
    _type = std::make_unique<nclass>(typeid(T).name(), sizeof(T),
                                     &ntype_ops_traits<T>::instance().ops);
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