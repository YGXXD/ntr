#pragma once

#include "nregistrar.h"

namespace ntr
{

template <typename T>
auto& nregistrar::factory_wrapper()
{
    return nfactory<make_etype<T>(), T>::instance();
}

template <typename T>
inline const ntype* nregistrar::get_type()
{
    return factory_wrapper<T>()._type.get();
}

template <typename T>
inline auto& nregistrar::regist(std::string_view name)
{
    auto& fact = factory_wrapper<T>();
    regist(name, fact._type.get());
    return fact;
}

} // namespace ntr