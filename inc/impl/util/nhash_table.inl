//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../util/nhash_table.hpp"

namespace ntr
{

template <typename T>
nhash_table_iterator<T>::nhash_table_iterator(nhash_table_bucket<value_type>* bucket,
                                              nhash_table_bucket<value_type>* end)
    : _bucket(bucket), _end(end) {};

template <typename T>
NTR_INLINE nhash_table_iterator<T>& nhash_table_iterator<T>::operator++()
{
    for (_bucket = _bucket + 1; _bucket != _end; ++_bucket)
        if (_bucket->valid)
            return *this;
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
    return _bucket->element;
}

template <typename T>
NTR_INLINE typename nhash_table_iterator<T>::pointer
nhash_table_iterator<T>::operator->() const
{
    return &_bucket->element;
}

NTR_INLINE uint32_t nhash_table_growth_capacity(uint32_t capacity)
{
    return capacity == 0 ? 32 : capacity * 2;
}

template <class TableTraits, class Hash, class Allocator>
nhash_table<TableTraits, Hash, Allocator>::nhash_table()
    : _size(0), _capacity(0), _buckets(nullptr)
{
}

template <class TableTraits, class Hash, class Allocator>
nhash_table<TableTraits, Hash, Allocator>::nhash_table(const nhash_table& other)
    : _size(other._size), _capacity(other._capacity), _buckets(nullptr)
{
    if (_capacity > 0)
    {
        _buckets = Allocator().allocate(_capacity);
        if constexpr (std::is_trivially_copyable_v<element_type>)
            std::memcpy(_buckets, other._buckets, _capacity * sizeof(bucket_type));
        else
        {
            std::memset(_buckets, 0, _capacity * sizeof(bucket_type));
            for (uint32_t i = 0; i < _capacity; ++i)
            {
                if (other._buckets[i].valid)
                {
                    _buckets[i].valid = 1;
                    _buckets[i].distance = other._buckets[i].distance;
                    new (&_buckets[i].element) element_type(other._buckets[i].element);
                }
            }
        }
    }
}

template <class TableTraits, class Hash, class Allocator>
nhash_table<TableTraits, Hash, Allocator>::nhash_table(nhash_table&& other)
    : _size(other._size), _capacity(other._capacity), _buckets(other._buckets)
{
    other._size = 0;
    other._capacity = 0;
    other._buckets = nullptr;
}

template <class TableTraits, class Hash, class Allocator>
nhash_table<TableTraits, Hash, Allocator>::~nhash_table()
{
    if constexpr (!std::is_trivially_copyable_v<element_type>)
    {
        for (uint32_t i = 0; i < _capacity; ++i)
            if (_buckets[i].valid)
                _buckets[i].element.~element_type();
    }
    if (_buckets)
        Allocator().deallocate(_buckets, _capacity);
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE void nhash_table<TableTraits, Hash, Allocator>::reserve(uint32_t new_capacity)
{
    if (new_capacity <= _capacity)
        return;

    Allocator allocator {};
    bucket_type* old_buckets = _buckets;
    uint32_t old_capacity = _capacity;
    _capacity = new_capacity;
    _buckets = allocator.allocate(_capacity);
    std::memset(_buckets, 0, _capacity * sizeof(bucket_type));
    if (_size > 0)
    {
        _size = 0;
        for (uint32_t i = 0; i < old_capacity; ++i)
        {
            if (old_buckets[i].valid)
            {
                insert_force(std::move(old_buckets[i].element));
                if (!std::is_trivially_copyable_v<element_type>)
                    old_buckets[i].element.~element_type();
            }
        }
    }
    if (old_buckets)
        allocator.deallocate(old_buckets, old_capacity);
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE void
nhash_table<TableTraits, Hash, Allocator>::insert(const element_type& element)
{
    insert(element_type(element));
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE void nhash_table<TableTraits, Hash, Allocator>::insert(element_type&& element)
{
    uint32_t position = find_position(get_key(element));
    if (position == _capacity)
        insert_force(std::move(element));
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE bool nhash_table<TableTraits, Hash, Allocator>::remove(const key_type& key)
{
    uint32_t position = find_position(key);
    if (position != _capacity)
    {
        _buckets[position].valid = 0;
        _buckets[position].distance = 0;
        if constexpr (!std::is_trivially_copyable_v<element_type>)
            _buckets[position].element.~element_type();
        --_size;

        uint32_t next_position = (position + 1) % _capacity;
        while (_buckets[next_position].valid && _buckets[next_position].distance > 0)
        {
            std::swap(_buckets[position], _buckets[next_position]);
            --_buckets[position].distance;
            position = next_position;
            next_position = (next_position + 1) % _capacity;
        }
        return true;
    }
    return false;
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE bool nhash_table<TableTraits, Hash, Allocator>::remove(const iterator& it)
{
    return remove(get_key(*it));
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE bool
nhash_table<TableTraits, Hash, Allocator>::contains(const key_type& key) const
{
    return find_position(key) != _capacity;
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE void nhash_table<TableTraits, Hash, Allocator>::clear()
{
    if (_size > 0)
    {
        if constexpr (std::is_trivially_copyable_v<element_type>)
            std::memset(_buckets, 0, _capacity * sizeof(bucket_type));
        else
        {
            for (uint32_t i = 0; i < _capacity; ++i)
                if (_buckets[i].valid)
                {
                    _buckets[i].valid = 0;
                    _buckets[i].distance = 0;
                    _buckets[i].element.~element_type();
                }
        }
        _size = 0;
    }
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE uint32_t nhash_table<TableTraits, Hash, Allocator>::size() const
{
    return _size;
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE bool nhash_table<TableTraits, Hash, Allocator>::empty() const
{
    return _size == 0;
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE typename nhash_table<TableTraits, Hash, Allocator>::iterator
nhash_table<TableTraits, Hash, Allocator>::find(const key_type& key) const
{
    return iterator(_buckets + find_position(key), _buckets + _capacity);
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE typename nhash_table<TableTraits, Hash, Allocator>::iterator
nhash_table<TableTraits, Hash, Allocator>::begin() const
{
    bucket_type* bucket = _buckets;
    bucket_type* end = _buckets + _capacity;
    for (; bucket != end; ++bucket)
        if (bucket->valid)
            break;
    return iterator(bucket, end);
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE typename nhash_table<TableTraits, Hash, Allocator>::iterator
nhash_table<TableTraits, Hash, Allocator>::end() const
{
    bucket_type* end = _buckets + _capacity;
    return iterator(end, end);
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE uint32_t
nhash_table<TableTraits, Hash, Allocator>::insert_force(element_type&& insert_element)
{
    if (_size >= _capacity * 4 / 5)
        reserve(nhash_table_growth_capacity(_capacity));

    uint32_t position = Hash()(get_key(insert_element)) % _capacity;
    uint16_t distance = 0;
    while (true)
    {
        bucket_type& bucket = _buckets[position];
        if (!bucket.valid)
        {
            if (std::is_trivially_copyable_v<element_type>)
                bucket.element = std::move(insert_element);
            else
                new (&bucket.element) element_type(std::move(insert_element));
            bucket.valid = 1;
            bucket.distance = distance;
            ++_size;
            return position;
        }
        if (distance > bucket.distance)
        {
            std::swap(bucket.element, insert_element);
            std::swap(bucket.distance, distance);
        }
        position = (position + 1) % _capacity;
        ++distance;
    }
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE uint32_t
nhash_table<TableTraits, Hash, Allocator>::find_position(const key_type& key) const
{
    if (_size == 0)
        return _capacity;
    uint32_t position = Hash()(key) % _capacity;
    uint32_t distance = 0;
    while (_buckets[position].valid)
    {
        if (get_key(_buckets[position].element) == key)
            return position;
        if (distance > _buckets[position].distance)
            break;
        position = (position + 1) % _capacity;
        ++distance;
    };
    return _capacity;
}

} // namespace ntr