//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/ntype_ops_factory.hpp"

namespace ntr
{

template <typename T>
ntype_ops_factory<T>::ntype_ops_factory() : ops()
{
    if constexpr (std::is_default_constructible_v<T>)
    {
        ops.default_construct = [](void* self_data) -> void
        {
            new (self_data) T();
        };
    }
    if constexpr (std::is_copy_constructible_v<T>)
    {
        ops.copy_construct = [](void* self_data, const void* const other_data) -> void
        {
            new (self_data) T(*static_cast<const T*>(other_data));
        };
    }
    if constexpr (std::is_move_constructible_v<T>)
    {
        ops.move_construct = [](void* self_data, void* other_data) -> void
        {
            new (self_data) T(std::move(*static_cast<T*>(other_data)));
        };
    }
    if constexpr (std::is_destructible_v<T>)
    {
        ops.destruct = [](void* self_data) -> void
        {
            static_cast<T*>(self_data)->~T();
        };
    }
}

} // namespace ntr