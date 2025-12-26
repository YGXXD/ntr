//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../type/ntype.hpp"
#include "../type/nnumeric.hpp"
#include "../type/ncontainer.hpp"

namespace ntr
{

template <typename T>
struct is_etype_type
{
    constexpr static bool value = !std::is_array_v<T> && !std::is_const_v<T> &&
                                  !std::is_volatile_v<T> && !std::is_reference_v<T>;
};

template <typename T>
struct is_etype_numeric
{
    template <typename Tuple>
    struct impl;
    template <typename... Ts>
    struct impl<std::tuple<Ts...>>
    {
        constexpr static bool value = std::disjunction_v<std::is_same<T, Ts>...>;
    };
    constexpr static bool value = impl<nnumeric::numeric_types>::value;
};

template <typename T>
struct is_etype_enum
{
    constexpr static bool value =
        std::is_enum_v<T> && !std::is_const_v<T> && !std::is_volatile_v<T>;
};

template <typename T>
struct is_etype_container;
template <typename T>
struct is_etype_class
{
    constexpr static bool value = !is_etype_container<T>::value && std::is_class_v<T> &&
                                  !std::is_const_v<T> && !std::is_volatile_v<T>;
};

template <typename T>
struct is_etype_pointer
{
    constexpr static bool value =
        std::is_pointer_v<T> && !std::is_const_v<T> && !std::is_volatile_v<T>;
};

template <typename T>
struct is_etype_container
{
    constexpr static bool value = ncontainer::list_templates::append<
        ncontainer::map_templates>::type::contains_type<T>::value;
};

template <typename T>
struct make_etype
{
    static_assert(is_etype_type<T>::value,
                  "make_etype : template parameter \"T\" is not valid type");
    constexpr static ntype::etype value = []()
    {
        if constexpr (is_etype_numeric<T>::value)
            return ntype::etype::enumeric;
        else if constexpr (is_etype_enum<T>::value)
            return ntype::etype::eenum;
        else if constexpr (is_etype_class<T>::value)
            return ntype::etype::eclass;
        else if constexpr (is_etype_pointer<T>::value)
            return ntype::etype::epointer;
        else if constexpr (is_etype_container<T>::value)
            return ntype::etype::econtainer;
        else
            return ntype::etype::eunknown;
    }();
};

template <typename T>
struct make_enumeric
{
    static_assert(is_etype_numeric<T>::value,
                  "make_enumeric : template parameter \"T\" is not valid numeric type");
    template <typename Tuple>
    struct impl;
    template <>
    struct impl<std::tuple<>>
    {
        constexpr static size_t value = 0;
    };
    template <typename FirstT, typename... OtherTs>
    struct impl<std::tuple<FirstT, OtherTs...>>
    {
        constexpr static size_t value = std::conditional_t<
            std::is_same_v<T, FirstT>, std::integral_constant<size_t, 0>,
            std::integral_constant<size_t,
                                   1 + impl<std::tuple<OtherTs...>>::value>>::value;
    };
    constexpr static nnumeric::enumeric value =
        static_cast<nnumeric::enumeric>(impl<nnumeric::numeric_types>::value);
};

template <typename T>
struct is_econtainer_map
{
    static_assert(
        is_etype_container<T>::value,
        "is_econtainer_map : template parameter \"T\" is not valid container type");
    constexpr static bool value = ncontainer::map_templates::contains_type<T>::value;
};

} // namespace ntr
