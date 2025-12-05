//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../tool/ntable.hpp"
#include "../../tool/ntraits.hpp"

namespace ntr
{

constexpr NTR_INLINE size_t bucket_size(size_t item_size)
{
    return sizeof(bucket_info) + item_size;
}

NTR_INLINE void* bucket_pp(void* _bucket, size_t item_size)
{
    return static_cast<char*>(_bucket) + bucket_size(item_size);
}

NTR_INLINE void* get_item(void* _bucket)
{
    return static_cast<char*>(_bucket) + sizeof(bucket_info);
}

NTR_INLINE void* get_bucket(void* buckets, uint32_t position, size_t item_size)
{
    return static_cast<char*>(buckets) + position * bucket_size(item_size);
}

template <typename T>
table_iterator<T>::table_iterator(void* bucket, void* end)
    : _bucket(bucket), _end(end) {};

template <typename T>
NTR_INLINE table_iterator<T>& table_iterator<T>::operator++()
{
    for (_bucket = bucket_pp(_bucket, sizeof(T)); _bucket != _end;
         _bucket = bucket_pp(_bucket, sizeof(T)))
    {
        if (static_cast<bucket_info*>(_bucket)->valid)
            return *this;
    }
    return *this;
}

template <typename T>
NTR_INLINE table_iterator<T> table_iterator<T>::operator++(int)
{
    table_iterator temp = *this;
    ++*this;
    return temp;
}

template <typename T>
NTR_INLINE bool table_iterator<T>::operator==(const table_iterator& other) const
{
    return _bucket == other._bucket;
}

template <typename T>
NTR_INLINE bool table_iterator<T>::operator!=(const table_iterator& other) const
{
    return _bucket != other._bucket;
}

template <typename T>
NTR_INLINE typename table_iterator<T>::reference table_iterator<T>::operator*() const
{
    return *static_cast<T*>(get_item(_bucket));
}

template <typename T>
NTR_INLINE typename table_iterator<T>::pointer table_iterator<T>::operator->() const
{
    return static_cast<T*>(get_item(_bucket));
}

template <class TableTraits, class Hash>
nhash_table<TableTraits, Hash>::nhash_table() : ntable()
{
}

template <class TableTraits, class Hash>
nhash_table<TableTraits, Hash>::nhash_table(const nhash_table& other)
{
    copy_init(other, item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class TableTraits, class Hash>
nhash_table<TableTraits, Hash>::nhash_table(nhash_table&& other)
{
    move_init(std::move(other));
}

template <class TableTraits, class Hash>
nhash_table<TableTraits, Hash>::~nhash_table()
{
    destruct(item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class TableTraits, class Hash>
NTR_INLINE void nhash_table<TableTraits, Hash>::reserve(uint32_t new_capacity)
{
    ntable::reserve(new_capacity, item_size, hash, get_key,
                    &ntype_ops_traits<item_type>::instance().ops);
}

template <class TableTraits, class Hash>
NTR_INLINE void nhash_table<TableTraits, Hash>::insert(const item_type& item)
{
    ntable::insert(const_cast<void*>(&item), item_size, hash, get_key, key_equal,
                   &ntype_ops_traits<item_type>::instance().ops, false);
}

template <class TableTraits, class Hash>
NTR_INLINE void nhash_table<TableTraits, Hash>::insert(item_type&& item)
{
    ntable::insert(&item, item_size, hash, get_key, key_equal,
                   &ntype_ops_traits<item_type>::instance().ops, true);
}

template <class TableTraits, class Hash>
NTR_INLINE bool nhash_table<TableTraits, Hash>::remove(const key_type& key)
{
    return ntable::remove(const_cast<key_type*>(&key), item_size, hash, get_key,
                          key_equal, &ntype_ops_traits<item_type>::instance().ops);
}

template <class TableTraits, class Hash>
NTR_INLINE bool nhash_table<TableTraits, Hash>::remove(key_type&& key)
{
    return ntable::remove(&key, item_size, hash, get_key, key_equal,
                          &ntype_ops_traits<item_type>::instance().ops);
}

template <class TableTraits, class Hash>
NTR_INLINE bool nhash_table<TableTraits, Hash>::remove(const iterator& it)
{
    return ntable::remove(const_cast<key_type*>(&it->first), item_size, hash, get_key,
                          key_equal, &ntype_ops_traits<item_type>::instance().ops);
}

template <class TableTraits, class Hash>
NTR_INLINE bool nhash_table<TableTraits, Hash>::contains(const key_type& key) const
{
    return ntable::contains(const_cast<key_type*>(&key), item_size, hash, get_key,
                            key_equal);
}

template <class TableTraits, class Hash>
NTR_INLINE bool nhash_table<TableTraits, Hash>::contains(key_type&& key) const
{
    return ntable::contains(&key, item_size, hash, get_key, key_equal);
}

template <class TableTraits, class Hash>
NTR_INLINE void nhash_table<TableTraits, Hash>::clear()
{
    return ntable::clear(item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class TableTraits, class Hash>
NTR_INLINE typename nhash_table<TableTraits, Hash>::iterator
nhash_table<TableTraits, Hash>::find(const key_type& key) const
{
    return iterator(
        ntable::find(const_cast<key_type*>(&key), item_size, hash, get_key, key_equal),
        ntable::end(item_size));
}

template <class TableTraits, class Hash>
NTR_INLINE typename nhash_table<TableTraits, Hash>::iterator
nhash_table<TableTraits, Hash>::find(key_type&& key) const
{
    return iterator(ntable::find(&key, item_size, hash, get_key, key_equal),
                    ntable::end(item_size));
}

template <class TableTraits, class Hash>
NTR_INLINE typename nhash_table<TableTraits, Hash>::iterator
nhash_table<TableTraits, Hash>::begin() const
{
    return iterator(ntable::begin(item_size), ntable::end(item_size));
}

template <class TableTraits, class Hash>
NTR_INLINE typename nhash_table<TableTraits, Hash>::iterator
nhash_table<TableTraits, Hash>::end() const
{
    return iterator(ntable::end(item_size), ntable::end(item_size));
}

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