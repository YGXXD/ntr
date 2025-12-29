//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/nregistrar.hpp"
#include "../../core/ntype_factory.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE auto& nregistrar::factory_wrapper()
{
    using ntr_type = std::enable_if_t<
        !std::is_array_v<std::remove_cv_t<std::remove_reference_t<T>>>,
        std::conditional_t<std::is_pointer_v<T>,
                           std::add_pointer_t<std::remove_cv_t<
                               std::remove_reference_t<std::remove_pointer_t<T>>>>,
                           std::remove_cv_t<std::remove_reference_t<T>>>>;
    return ntype_factory<make_etype<ntr_type>::value, ntr_type>::instance();
}

template <typename T>
NTR_INLINE const auto* nregistrar::get_type()
{
    return &factory_wrapper<T>()._type;
}

template <typename T>
NTR_INLINE auto& nregistrar::regist_type(std::string_view name)
{
    static_assert(is_etype_type<T>::value,
                  "nregistrar::regist_type : template parameter \"T\" is not valid type");
    auto& fact = factory_wrapper<T>();
    regist_type(name, &fact._type);
    return fact;
}

} // namespace ntr

#include "nwrapper.inl"
#include "nobject.inl"
#include "ntype_factory.inl"
#include "ntype_ops_factory.inl"
#include "nfield_factory.inl"
#include "ncontainer_ops_factory.inl"