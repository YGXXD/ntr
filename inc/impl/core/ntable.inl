//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/ntable.hpp"
#include "../../type/ntraits.hpp"

namespace ntr
{

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
NTR_INLINE T& table_iterator<T>::operator*()
{
    return *static_cast<T*>(get_item(_bucket));
}

template <typename T>
NTR_INLINE const T& table_iterator<T>::operator*() const
{
    return *static_cast<const T*>(get_item(_bucket));
}

template <typename T>
NTR_INLINE T* table_iterator<T>::operator->()
{
    return static_cast<T*>(get_item(_bucket));
}

template <typename T>
NTR_INLINE const T* table_iterator<T>::operator->() const
{
    return static_cast<const T*>(get_item(_bucket));
}

template <class Key, class Value, class Hash>
nhash_map<Key, Value, Hash>::nhash_map() : ntable()
{
}

template <class Key, class Value, class Hash>
nhash_map<Key, Value, Hash>::nhash_map(const nhash_map& other)
{
    copy_init(other, item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Key, class Value, class Hash>
nhash_map<Key, Value, Hash>::nhash_map(nhash_map&& other)
{
    move_init(std::move(other));
}

template <class Key, class Value, class Hash>
nhash_map<Key, Value, Hash>::~nhash_map()
{
    destruct(item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Key, class Value, class Hash>
NTR_INLINE void nhash_map<Key, Value, Hash>::reserve(uint32_t new_capacity)
{
    ntable::reserve(new_capacity, item_size, hash, get_key);
}

template <class Key, class Value, class Hash>
NTR_INLINE void nhash_map<Key, Value, Hash>::insert(const item_type& item)
{
    ntable::insert(const_cast<void*>(&item), item_size, hash, get_key, key_equal, 0,
                   &ntype_ops_traits<item_type>::instance().ops, update_value);
}

template <class Key, class Value, class Hash>
NTR_INLINE void nhash_map<Key, Value, Hash>::insert(item_type&& item)
{
    ntable::insert(&item, item_size, hash, get_key, key_equal, 1,
                   &ntype_ops_traits<item_type>::instance().ops, update_value);
}

template <class Key, class Value, class Hash>
NTR_INLINE void nhash_map<Key, Value, Hash>::insert(const Key& key, const Value& value)
{
    uint32_t position = ntable::find_position(const_cast<Key*>(&key), item_size, hash,
                                              get_key, key_equal);
    if (position == std::numeric_limits<uint32_t>::max())
    {
        item_type item = { key, value };
        position = ntable::insert_force(&item, item_size, hash, get_key, 1,
                                        &ntype_ops_traits<item_type>::instance().ops);
    }
    else
        reinterpret_cast<item_type*>(get_item(get_bucket(_buckets, position, item_size)))
            ->second = value;
}

template <class Key, class Value, class Hash>
NTR_INLINE void nhash_map<Key, Value, Hash>::insert(const Key& key, Value&& value)
{
    uint32_t position = ntable::find_position(const_cast<Key*>(&key), item_size, hash,
                                              get_key, key_equal);
    if (position == std::numeric_limits<uint32_t>::max())
    {
        item_type item = { key, std::move(value) };
        position = ntable::insert_force(&item, item_size, hash, get_key, 1,
                                        &ntype_ops_traits<item_type>::instance().ops);
    }
    else
        static_cast<item_type*>(get_item(get_bucket(_buckets, position, item_size)))
            ->second = std::move(value);
}

template <class Key, class Value, class Hash>
NTR_INLINE bool nhash_map<Key, Value, Hash>::remove(const Key& key)
{
    return ntable::remove(const_cast<Key*>(&key), item_size, hash, get_key, key_equal,
                          &ntype_ops_traits<item_type>::instance().ops);
}

template <class Key, class Value, class Hash>
NTR_INLINE bool nhash_map<Key, Value, Hash>::remove(Key&& key)
{
    return ntable::remove(&key, item_size, hash, get_key, key_equal,
                          &ntype_ops_traits<item_type>::instance().ops);
}

template <class Key, class Value, class Hash>
NTR_INLINE bool nhash_map<Key, Value, Hash>::contains(const Key& key) const
{
    return ntable::contains(const_cast<Key*>(&key), item_size, hash, get_key, key_equal);
}

template <class Key, class Value, class Hash>
NTR_INLINE bool nhash_map<Key, Value, Hash>::contains(Key&& key) const
{
    return ntable::contains(&key, item_size, hash, get_key, key_equal);
}

template <class Key, class Value, class Hash>
NTR_INLINE typename nhash_map<Key, Value, Hash>::iterator
nhash_map<Key, Value, Hash>::find(const Key& key) const
{
    return iterator(
        ntable::find(const_cast<Key*>(&key), item_size, hash, get_key, key_equal),
        ntable::end(item_size));
}

template <class Key, class Value, class Hash>
NTR_INLINE typename nhash_map<Key, Value, Hash>::iterator
nhash_map<Key, Value, Hash>::find(Key&& key) const
{
    return iterator(ntable::find(&key, item_size, hash, get_key, key_equal),
                    ntable::end(item_size));
}

template <class Key, class Value, class Hash>
NTR_INLINE typename nhash_map<Key, Value, Hash>::iterator
nhash_map<Key, Value, Hash>::begin() const
{
    return iterator(ntable::begin(item_size), ntable::end(item_size));
}

template <class Key, class Value, class Hash>
NTR_INLINE typename nhash_map<Key, Value, Hash>::iterator
nhash_map<Key, Value, Hash>::end() const
{
    return iterator(ntable::end(item_size), ntable::end(item_size));
}

template <class Key, class Value, class Hash>
NTR_INLINE Value& nhash_map<Key, Value, Hash>::operator[](const Key& key)
{
    uint32_t position = ntable::find_position(const_cast<Key*>(&key), item_size, hash,
                                              get_key, key_equal);
    if (position == std::numeric_limits<uint32_t>::max())
        throw std::out_of_range("nhash_map<Key, Value, Hash>::operator[] : invalid key");
    return *static_cast<item_type*>(get_item(get_bucket(_buckets, position, item_size)));
}

template <class Key, class Value, class Hash>
NTR_INLINE const Value& nhash_map<Key, Value, Hash>::operator[](const Key& key) const
{
    uint32_t position = ntable::find_position(const_cast<Key*>(&key), item_size, hash,
                                              get_key, key_equal);
    if (position == std::numeric_limits<uint32_t>::max())
        throw std::out_of_range("nhash_map<Key, Value, Hash>::operator[] : invalid key");
    return *static_cast<const item_type*>(
        get_item(get_bucket(_buckets, position, item_size)));
}

} // namespace ntr