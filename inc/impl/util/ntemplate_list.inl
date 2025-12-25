//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../util/ntemplate_list.hpp"

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
template <template <typename...> class Ftp>
NTR_INLINE constexpr size_t ntemplate_list<Tps...>::find_index()
{
    size_t index = 0;
    ((index += (is_template_same<Ftp, Tps>::value ? 0 : 1)), ...);
    return index;
};

} // namespace ntr