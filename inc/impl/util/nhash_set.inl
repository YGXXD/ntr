//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../util/nhash_set.hpp"

namespace ntr
{

template <class Value>
const typename nhash_set_table_traits<Value>::key_type&
nhash_set_table_traits<Value>::get_key(const element_type& element)
{
    return element;
}

} // namespace ntr