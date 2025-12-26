//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../util/nhash_map.hpp"

#include <stdexcept>

namespace ntr
{

template <class Key, class Value>
const typename nhash_map_table_traits<Key, Value>::key_type&
nhash_map_table_traits<Key, Value>::get_key(const element_type& element)
{
    return element.first;
}

template <class Key, class Value, class Hash, class Allocator>
NTR_INLINE void
nhash_map<Key, Value, Hash, Allocator>::insert_or_assign(const key_type& key,
                                                         const value_type& value)
{
    forward_insert_or_assign(key, value);
}

template <class Key, class Value, class Hash, class Allocator>
NTR_INLINE void
nhash_map<Key, Value, Hash, Allocator>::insert_or_assign(const key_type& key,
                                                         value_type&& value)
{
    forward_insert_or_assign(key, std::move(value));
}

template <class Key, class Value, class Hash, class Allocator>
NTR_INLINE typename nhash_map<Key, Value, Hash, Allocator>::value_type&
nhash_map<Key, Value, Hash, Allocator>::at(const key_type& key)
{
    uint32_t position = hash_table_type::find_position(key);
    if (position == _capacity)
        throw std::out_of_range(
            "nhash_map<Key, Value, Hash, Allocator>::at : invalid key");
    return _buckets[position].element.second;
}

template <class Key, class Value, class Hash, class Allocator>
NTR_INLINE const typename nhash_map<Key, Value, Hash, Allocator>::value_type&
nhash_map<Key, Value, Hash, Allocator>::at(const key_type& key) const
{
    uint32_t position = hash_table_type::find_position(key);
    if (position == _capacity)
        throw std::out_of_range(
            "nhash_map<Key, Value, Hash, Allocator>::at : invalid key");
    return _buckets[position].element.second;
}

template <class Key, class Value, class Hash, class Allocator>
NTR_INLINE typename nhash_map<Key, Value, Hash, Allocator>::value_type&
nhash_map<Key, Value, Hash, Allocator>::operator[](const key_type& key)
{
    uint32_t position = hash_table_type::find_position(key);
    if (position == _capacity)
        position = hash_table_type::insert_force(element_type(key, value_type()));
    return _buckets[position].element.second;
}

template <class Key, class Value, class Hash, class Allocator>
NTR_INLINE const typename nhash_map<Key, Value, Hash, Allocator>::value_type&
nhash_map<Key, Value, Hash, Allocator>::operator[](const key_type& key) const
{
    uint32_t position = hash_table_type::find_position(key);
    if (position == _capacity)
        position = hash_table_type::insert_force(element_type(key, value_type()));
    return _buckets[position].element.second;
}

template <class Key, class Value, class Hash, class Allocator>
template <class ValueType>
NTR_INLINE void
nhash_map<Key, Value, Hash, Allocator>::forward_insert_or_assign(const key_type& key,
                                                          ValueType&& value)
{
    uint32_t position = hash_table_type::find_position(key);
    if (position == _capacity)
        hash_table_type::insert_force(element_type(key, std::forward<ValueType>(value)));
    else
        _buckets[position].element.second = std::forward<ValueType>(value);
}

} // namespace ntr