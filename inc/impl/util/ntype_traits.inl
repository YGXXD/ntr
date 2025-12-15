//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../util/ntype_traits.hpp"
#include "../../util/nvector.hpp"
#include "../../util/nhash_map.hpp"
#include "../../util/nhash_set.hpp"

namespace ntr
{

template <typename T>
struct is_container : std::false_type
{
};

template <typename... Args>
struct is_container<nvector<Args...>> : std::true_type
{
};

template <typename... Args>
struct is_container<nhash_map<Args...>> : std::true_type
{
};

template <typename... Args>
struct is_container<nhash_set<Args...>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_container_v = is_container<T>::value;

template <typename T>
struct is_container_iterator : std::false_type
{
};

template <typename... Args>
struct is_container_iterator<nvector_iterator<Args...>> : std::true_type
{
};

template <typename... Args>
struct is_container_iterator<nhash_table_iterator<Args...>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_container_iterator_v = is_container_iterator<T>::value;

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
    return std::is_class_v<T> && !is_container_v<T> && !is_container_iterator_v<T> &&
           !std::is_const_v<T> && !std::is_volatile_v<T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_pointer()
{
    return std::is_pointer_v<T> && !std::is_const_v<T> && !std::is_volatile_v<T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_container()
{
    return is_container_v<T>;
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
    else if constexpr (is_etype_container<T>())
        return ntype::etype::econtainer;
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

} // namespace ntr