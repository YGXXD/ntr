//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"

#include <cstddef>

namespace ntr
{

template <template <typename...> class... Tps>
struct ntemplate_list
{
    template <template <typename...> class Ftp>
    NTR_INLINE static constexpr size_t find_index();

    constexpr static size_t size = sizeof...(Tps);

    template <template <typename...> class Ctp>
    constexpr static bool contains = find_index<Ctp>() < size;

    template <typename TpList>
    struct append;
    template <template <typename...> class... Aps>
    struct append<ntemplate_list<Aps...>>
    {
        using type = ntemplate_list<Tps..., Aps...>;
    };

    template <typename T>
    struct contains_type
    {
        constexpr static bool value = false;
    };
    template <template <typename...> class Ctp, typename... Args>
    struct contains_type<Ctp<Args...>>
    {
        constexpr static bool value = contains<Ctp>;
    };
};

} // namespace ntr

#include "../impl/util/ntemplate_list.inl"