#pragma once

#include "nfactory.h"
#include "nbasic.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

// ntype::etype::ebasic impl
template <typename T>
inline nfactory<ntype::etype::ebasic, T>&
nfactory<ntype::etype::ebasic, T>::init(std::string_view name)
{
    if (_type == nullptr)
        _type = std::make_unique<nbasic>(nbasic::to_ebasic<T>(), name);
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
nfactory<ntype::etype::eenum, T>::add(std::string_view name, T value)
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

} // namespace ntr