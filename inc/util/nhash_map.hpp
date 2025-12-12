//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "nhash_table.hpp"

namespace ntr
{

template <class Key, class Value>
struct nhash_map_table_traits
{
    using key_type = Key;
    using value_type = Value;
    using element_type = std::pair<Key, Value>;
    NTR_INLINE static const key_type& get_key(const element_type& element);
};

template <class Key, class Value, class Hash = std::hash<Key>,
          class Allocator = std::allocator<nhash_table_bucket<std::pair<Key, Value>>>>
class nhash_map : public nhash_table<nhash_map_table_traits<Key, Value>, Hash, Allocator>
{
    using hash_table_type =
        nhash_table<nhash_map_table_traits<Key, Value>, Hash, Allocator>;
    using hash_table_type::hash_table_type;
    using typename hash_table_type::key_type;
    using typename hash_table_type::value_type;

    static_assert(std::is_same_v<Key, key_type>);
    static_assert(std::is_same_v<Value, value_type>);

    using hash_table_type::_buckets;
    using hash_table_type::_capacity;

public:
    using typename hash_table_type::element_type;
    using typename hash_table_type::iterator;

    using hash_table_type::insert;
    NTR_INLINE void insert(const key_type& key, const value_type& value);
    NTR_INLINE void insert(const key_type& key, value_type&& value);
    NTR_INLINE value_type& at(const key_type& key);
    NTR_INLINE const value_type& at(const key_type& key) const;
    NTR_INLINE value_type& operator[](const key_type& key);
    NTR_INLINE const value_type& operator[](const key_type& key) const;
};

} // namespace ntr

#include "../impl/util/nhash_map.inl"