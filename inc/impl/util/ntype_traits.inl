//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../util/ntype_traits.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE constexpr bool is_etype_type()
{
    return !std::is_array_v<T> && !std::is_const_v<T> && !std::is_volatile_v<T> &&
           !std::is_reference_v<T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_numeric()
{
    return std::apply([](auto&&... args)
    { return (std::is_same_v<std::decay_t<decltype(args)>, T> || ...); },
                      nnumeric::numeric_types {});
}

template <typename T>
NTR_INLINE constexpr bool is_etype_enum()
{
    return std::is_enum_v<T> && !std::is_const_v<T> && !std::is_volatile_v<T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_class()
{
    return std::is_class_v<T> && !std::is_const_v<T> && !std::is_volatile_v<T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_pointer()
{
    return std::is_pointer_v<T> && !std::is_const_v<T> && !std::is_volatile_v<T>;
}

template <typename T>
NTR_INLINE constexpr ntype::etype make_etype()
{
    static_assert(is_etype_type<T>(),
                  "make_etype : template parameter \"T\" is not valid type");
    if constexpr (is_etype_numeric<T>())
        return ntype::etype::enumeric;
    else if constexpr (is_etype_enum<T>())
        return ntype::etype::eenum;
    else if constexpr (is_etype_class<T>())
        return ntype::etype::eclass;
    else if constexpr (is_etype_pointer<T>())
        return ntype::etype::epointer;
    else
        return ntype::etype::eunknown;
}

template <typename T>
NTR_INLINE constexpr nnumeric::enumeric make_enumeric()
{
    static_assert(is_etype_numeric<T>(),
                  "make_enumeric : template parameter \"T\" is not valid numeric type");
    return std::apply([](auto&&... args)
    {
        size_t index = 0;
        size_t result = static_cast<size_t>(-1);
        ((std::is_same_v<std::decay_t<decltype(args)>, T> ? (result = index, 0)
                                                          : (++index, 0)),
         ...);
        return static_cast<nnumeric::enumeric>(result);
    }, nnumeric::numeric_types {});
}

template <typename T>
NTR_INLINE constexpr uint8_t make_pointer_depth()
{
    if constexpr (std::is_pointer_v<T>)
        return 1 + make_pointer_depth<std::remove_pointer_t<T>>();
    else
        return 0;
}

template <typename T>
ntype_ops_traits<T>::ntype_ops_traits() : ops()
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

template <typename T>
ntype_ops_traits<T*>::ntype_ops_traits() : ops(ntype_ops_traits<void*>::instance().ops)
{
}

} // namespace ntr