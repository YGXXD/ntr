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
    using mt = make_type_t<T>;
    return ntype_factory<make_etype<mt>(), mt>::instance();
}

template <typename T>
NTR_INLINE const auto* nregistrar::get_type()
{
    return &factory_wrapper<T>()._type;
}

template <typename T>
NTR_INLINE auto& nregistrar::regist_type(std::string_view name)
{
    static_assert(is_etype_type<T>(),
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