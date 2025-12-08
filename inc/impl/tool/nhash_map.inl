//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../tool/nhash_map.hpp"
#include "../../tool/ntraits.hpp"

namespace ntr
{

template <class Key, class Value, class Hash>
NTR_INLINE void nhash_map<Key, Value, Hash>::insert(const key_type& key,
                                                    const value_type& value)
{
    uint32_t position = ntable::find_position(const_cast<key_type*>(&key), item_size,
                                              hash, get_key, key_equal);
    if (position == _capacity)
    {
        item_type item = { key, value };
        ntable::insert_force(&item, item_size, hash, get_key,
                             &ntype_ops_traits<item_type>::instance().ops, true);
    }
}

template <class Key, class Value, class Hash>
NTR_INLINE void nhash_map<Key, Value, Hash>::insert(const key_type& key,
                                                    value_type&& value)
{
    uint32_t position = ntable::find_position(const_cast<key_type*>(&key), item_size,
                                              hash, get_key, key_equal);
    if (position == _capacity)
    {
        item_type item = { key, std::move(value) };
        ntable::insert_force(&item, item_size, hash, get_key,
                             &ntype_ops_traits<item_type>::instance().ops, true);
    }
}

template <class Key, class Value, class Hash>
NTR_INLINE typename nhash_map<Key, Value, Hash>::value_type&
nhash_map<Key, Value, Hash>::at(const key_type& key)
{
    uint32_t position = ntable::find_position(const_cast<key_type*>(&key), item_size,
                                              hash, get_key, key_equal);
    if (position == _capacity)
        throw std::out_of_range("nhash_map<Key, Value, Hash>::at : invalid key");
    return static_cast<item_type*>(get_item(get_bucket(_buckets, position, item_size)))
        ->second;
}

template <class Key, class Value, class Hash>
NTR_INLINE const typename nhash_map<Key, Value, Hash>::value_type&
nhash_map<Key, Value, Hash>::at(const key_type& key) const
{
    uint32_t position = ntable::find_position(const_cast<key_type*>(&key), item_size,
                                              hash, get_key, key_equal);
    if (position == _capacity)
        throw std::out_of_range("nhash_map<Key, Value, Hash>::at : invalid key");
    return static_cast<const item_type*>(
               get_item(get_bucket(_buckets, position, item_size)))
        ->second;
}

template <class Key, class Value, class Hash>
NTR_INLINE typename nhash_map<Key, Value, Hash>::value_type&
nhash_map<Key, Value, Hash>::operator[](const key_type& key)
{
    uint32_t position = ntable::find_position(const_cast<key_type*>(&key), item_size,
                                              hash, get_key, key_equal);
    if (position == _capacity)
    {
        item_type item = { key, Value() };
        position =
            ntable::insert_force(&item, item_size, hash, get_key,
                                 &ntype_ops_traits<item_type>::instance().ops, true);
    }
    return static_cast<item_type*>(get_item(get_bucket(_buckets, position, item_size)))
        ->second;
}

template <class Key, class Value, class Hash>
NTR_INLINE const typename nhash_map<Key, Value, Hash>::value_type&
nhash_map<Key, Value, Hash>::operator[](const key_type& key) const
{
    uint32_t position = ntable::find_position(const_cast<key_type*>(&key), item_size,
                                              hash, get_key, key_equal);
    if (position == _capacity)
    {
        item_type item = { key, Value() };
        position =
            ntable::insert_force(&item, item_size, hash, get_key,
                                 &ntype_ops_traits<item_type>::instance().ops, true);
    }
    return static_cast<const item_type*>(
               get_item(get_bucket(_buckets, position, item_size)))
        ->second;
}

} // namespace ntr