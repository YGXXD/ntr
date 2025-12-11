//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "nhash_table.hpp"

namespace ntr
{

template <class Value>
struct nhash_set_table_traits
{
    using key_type = Value;
    using value_type = Value;
    using element_type = Value;
    NTR_INLINE static const key_type& get_key(const element_type& element);
};

template <class Value, class Hash = std::hash<Value>,
          class Allocator = std::allocator<nhash_table_bucket<Value>>>
class nhash_set : public nhash_table<nhash_set_table_traits<Value>, Hash, Allocator>
{
    using hash_table_type = nhash_table<nhash_set_table_traits<Value>, Hash, Allocator>;
    using hash_table_type::hash_table_type;

public:
    using typename hash_table_type::element_type;
    using typename hash_table_type::iterator;
};

} // namespace ntr

#include "../impl/util/nhash_set.inl"