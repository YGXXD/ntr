#pragma once

#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE auto& nregistrar::factory_wrapper()
{
    using MakeType = decltype(make_type<T>());
    static_assert(!std::is_array_v<MakeType>,
                  "nregistrar::factory_wrapper : primitive type of template parameters "
                  "\"T\" cannot be an array");
    return nfactory<make_etype<MakeType>(), MakeType>::instance();
}

template <typename T>
NTR_INLINE const auto* nregistrar::get_type()
{
    return factory_wrapper<T>()._type.get();
}

template <typename T>
NTR_INLINE auto& nregistrar::regist_type(std::string_view name)
{
    auto& fact = factory_wrapper<T>();
    regist_type(name, fact._type.get());
    return fact;
}

} // namespace ntr