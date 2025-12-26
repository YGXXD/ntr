//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "nhash_table.hpp"

#include <utility>

namespace ntr
{

template <class Key, class Value>
struct nhash_map_table_traits
{
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<Key, Value>;
    NTR_INLINE static const key_type& get_key(const value_type& value);
};

template <class Key, class Value, class Hash = std::hash<Key>,
          class Allocator = std::allocator<nhash_table_bucket<std::pair<Key, Value>>>>
class nhash_map : public nhash_table<nhash_map_table_traits<Key, Value>, Hash, Allocator>
{
    using hash_table_type =
        nhash_table<nhash_map_table_traits<Key, Value>, Hash, Allocator>;
    using hash_table_type::hash_table_type;
    using typename hash_table_type::value_type;

    using hash_table_type::_buckets;
    using hash_table_type::_capacity;

public:
    using typename hash_table_type::iterator;
    using typename hash_table_type::key_type;
    using typename hash_table_type::mapped_type;

    static_assert(std::is_same_v<Key, key_type>);
    static_assert(std::is_same_v<Value, mapped_type>);

    NTR_INLINE void insert_or_assign(const key_type& key, const mapped_type& value);
    NTR_INLINE void insert_or_assign(const key_type& key, mapped_type&& value);
    NTR_INLINE mapped_type& at(const key_type& key);
    NTR_INLINE const mapped_type& at(const key_type& key) const;
    NTR_INLINE mapped_type& operator[](const key_type& key);
    NTR_INLINE const mapped_type& operator[](const key_type& key) const;

private:
    template <class ValueType>
    NTR_INLINE void forward_insert_or_assign(const key_type& key, ValueType&& value);
};

} // namespace ntr

#include "../impl/util/nhash_map.inl"