//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/nobject.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE T& nobject::as()
{
    return wrapper().unwrap<T&>();
}

template <typename T>
NTR_INLINE const T& nobject::as() const
{
    return wrapper().unwrap<const T&>();
}

} // namespace ntr