//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../tool/nhash_table.hpp"
#include "../../tool/ntraits.hpp"

namespace ntr
{

template <typename T>
nhash_table_iterator<T>::nhash_table_iterator(void* bucket, void* end)
    : _bucket(bucket), _end(end) {};

template <typename T>
NTR_INLINE nhash_table_iterator<T>& nhash_table_iterator<T>::operator++()
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
NTR_INLINE nhash_table_iterator<T> nhash_table_iterator<T>::operator++(int)
{
    nhash_table_iterator temp = *this;
    ++*this;
    return temp;
}

template <typename T>
NTR_INLINE bool
nhash_table_iterator<T>::operator==(const nhash_table_iterator& other) const
{
    return _bucket == other._bucket;
}

template <typename T>
NTR_INLINE bool
nhash_table_iterator<T>::operator!=(const nhash_table_iterator& other) const
{
    return _bucket != other._bucket;
}

template <typename T>
NTR_INLINE typename nhash_table_iterator<T>::reference
nhash_table_iterator<T>::operator*() const
{
    return *static_cast<T*>(get_item(_bucket));
}

template <typename T>
NTR_INLINE typename nhash_table_iterator<T>::pointer
nhash_table_iterator<T>::operator->() const
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

} // namespace ntr