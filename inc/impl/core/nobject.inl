//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/nobject.hpp"
#include "../../core/nregistrar.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE T& nobject::as()
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject::as : type mismatch");
    return *static_cast<T*>(data());
}

template <typename T>
NTR_INLINE const T& nobject::as() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject::as : type mismatch");
    return *static_cast<const T*>(data());
}

} // namespace ntr