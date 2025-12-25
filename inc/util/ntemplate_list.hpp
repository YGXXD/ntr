//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"

namespace ntr
{

template <template <typename...> class... Tps>
struct ntemplate_list
{
    template <typename TpList>
    struct append;
    template <template <typename...> class... Aps>
    struct append<ntemplate_list<Aps...>>
    {
        using type = ntemplate_list<Tps..., Aps...>;
    };

    template <template <typename...> class Ftp>
    NTR_INLINE static constexpr size_t find_index();

    constexpr static size_t size = sizeof...(Tps);

    template <template <typename...> class Ctp>
    constexpr static bool contains = find_index<Ctp>() < size;

    template <typename T>
    constexpr static bool contains_type = false;

    template <template <typename...> class Ctp, typename... Args>
    constexpr static bool contains_type<Ctp<Args...>> = contains<Ctp>;
};

} // namespace ntr

#include "../impl/util/ntemplate_list.inl"