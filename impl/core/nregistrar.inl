#pragma once

#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE auto& nregistrar::factory_wrapper()
{
    using MakeType = make_type_t<T>;
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
    static_assert(is_etype_type<T>(),
                  "nregistrar::regist_type : template parameter \"T\" is not valid type");
    auto& fact = factory_wrapper<T>();
    regist_type(name, fact._type.get());
    return fact;
}

} // namespace ntr