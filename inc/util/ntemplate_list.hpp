//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include <type_traits>

namespace ntr
{

template <template <typename...> class Tp1, template <typename...> class Tp2>
struct is_template_same : std::false_type
{
};

template <template <typename...> class Tp>
struct is_template_same<Tp, Tp> : std::true_type
{
};

template <template <typename...> class... Tps>
struct ntemplate_list
{
    constexpr static size_t size = sizeof...(Tps);

    template <typename TpList>
    struct append;
    template <template <typename...> class... Aps>
    struct append<ntemplate_list<Aps...>>
    {
        using type = ntemplate_list<Tps..., Aps...>;
    };

    template <template <typename...> class Ftp>
    struct find_index
    {
        template <template <typename...> class... AllTps>
        struct impl;
        template <template <typename...> class FirstTp>
        struct impl<FirstTp>
        {
            constexpr static size_t value =
                std::conditional_t<is_template_same<Ftp, FirstTp>::value,
                                   std::integral_constant<size_t, 0>,
                                   std::integral_constant<size_t, 1>>::value;
        };
        template <template <typename...> class FirstTp,
                  template <typename...> class... OtherTps>
        struct impl<FirstTp, OtherTps...>
        {
            constexpr static size_t value = std::conditional_t<
                is_template_same<Ftp, FirstTp>::value, std::integral_constant<size_t, 0>,
                std::integral_constant<size_t, 1 + impl<OtherTps...>::value>>::value;
        };
        constexpr static size_t value = impl<Tps...>::value;
    };

    template <template <typename...> class Ctp>
    struct contains
    {
        constexpr static bool value = find_index<Ctp>::value < size;
    };

    template <typename T>
    struct contains_type
    {
        constexpr static bool value = false;
    };
    template <template <typename...> class Ctp, typename... Args>
    struct contains_type<Ctp<Args...>>
    {
        constexpr static bool value = contains<Ctp>::value;
    };
};

} // namespace ntr