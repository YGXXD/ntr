//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/nwrapper.hpp"
#include "../../core/nregistrar.hpp"

namespace ntr
{

template <typename T, typename>
nwrapper::nwrapper(T&& value) : nwrapper(nregistrar::get_type<T>(), &value)
{
}

template <typename T>
NTR_INLINE auto&& nwrapper::unwrap() const
{
    using decay_type = std::decay_t<T>;
    using unwrap_type = std::conditional_t<
        std::is_rvalue_reference_v<T>, decay_type&&,
        std::conditional_t<std::is_lvalue_reference_v<T> &&
                               !std::is_const_v<std::remove_reference_t<T>>,
                           decay_type&, const decay_type&>>;
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nwrapper::unwrap : type mismatch");
    return static_cast<unwrap_type>(*static_cast<decay_type*>(_pdata));
}

template <typename T>
NTR_INLINE nwrapper nwrapper::cast_to() const
{
    return cast_to(nregistrar::get_type<T>());
}

} // namespace ntr