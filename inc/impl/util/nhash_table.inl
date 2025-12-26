//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../util/nhash_table.hpp"

#include <cstring>

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
    return _bucket->value;
}

template <typename T>
NTR_INLINE typename nhash_table_iterator<T>::pointer
nhash_table_iterator<T>::operator->() const
{
    return &_bucket->value;
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
        if constexpr (std::is_trivially_copyable_v<value_type>)
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
                    new (&_buckets[i].value) value_type(other._buckets[i].value);
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
nhash_table<TableTraits, Hash, Allocator>::nhash_table(
    std::initializer_list<value_type> list)
    : _size(0), _capacity(0), _buckets(nullptr)
{
    reserve(list.size() * 2);
    for (auto& value : list)
        insert(value);
}

template <class TableTraits, class Hash, class Allocator>
nhash_table<TableTraits, Hash, Allocator>::~nhash_table()
{
    if constexpr (!std::is_trivially_copyable_v<value_type>)
    {
        for (uint32_t i = 0; i < _capacity; ++i)
            if (_buckets[i].valid)
                _buckets[i].value.~value_type();
    }
    if (_buckets)
        Allocator().deallocate(_buckets, _capacity);
}

template <class TableTraits, class Hash, class Allocator>
nhash_table<TableTraits, Hash, Allocator>&
nhash_table<TableTraits, Hash, Allocator>::operator=(const nhash_table& other)
{
    if (this != &other)
    {
        nhash_table temp(other);
        std::swap(_size, temp._size);
        std::swap(_capacity, temp._capacity);
        std::swap(_buckets, temp._buckets);
    }
    return *this;
}

template <class TableTraits, class Hash, class Allocator>
nhash_table<TableTraits, Hash, Allocator>&
nhash_table<TableTraits, Hash, Allocator>::operator=(nhash_table&& other)
{
    if (this != &other)
    {
        nhash_table temp(std::move(other));
        std::swap(_size, temp._size);
        std::swap(_capacity, temp._capacity);
        std::swap(_buckets, temp._buckets);
    }
    return *this;
}

template <class TableTraits, class Hash, class Allocator>
void nhash_table<TableTraits, Hash, Allocator>::reserve(uint32_t new_capacity)
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
                insert_force(std::move(old_buckets[i].value));
                if (!std::is_trivially_copyable_v<value_type>)
                    old_buckets[i].value.~value_type();
            }
        }
    }
    if (old_buckets)
        allocator.deallocate(old_buckets, old_capacity);
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE void nhash_table<TableTraits, Hash, Allocator>::insert(const value_type& value)
{
    forward_insert(value);
}

template <class TableTraits, class Hash, class Allocator>
NTR_INLINE void nhash_table<TableTraits, Hash, Allocator>::insert(value_type&& value)
{
    forward_insert(std::move(value));
}

template <class TableTraits, class Hash, class Allocator>
bool nhash_table<TableTraits, Hash, Allocator>::remove(const key_type& key)
{
    uint32_t position = find_position(key);
    if (position != _capacity)
    {
        _buckets[position].valid = 0;
        _buckets[position].distance = 0;
        if constexpr (!std::is_trivially_copyable_v<value_type>)
            _buckets[position].value.~value_type();
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
void nhash_table<TableTraits, Hash, Allocator>::clear()
{
    if (_size > 0)
    {
        if constexpr (std::is_trivially_copyable_v<value_type>)
            std::memset(_buckets, 0, _capacity * sizeof(bucket_type));
        else
        {
            for (uint32_t i = 0; i < _capacity; ++i)
                if (_buckets[i].valid)
                {
                    _buckets[i].valid = 0;
                    _buckets[i].distance = 0;
                    _buckets[i].value.~value_type();
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
uint32_t nhash_table<TableTraits, Hash, Allocator>::insert_force(value_type&& value)
{
    if (_size >= _capacity * 4 / 5)
        reserve(nhash_table_growth_capacity(_capacity));

    value_type insert_value(std::move(value));
    uint32_t position = Hash()(get_key(insert_value)) % _capacity;
    uint16_t distance = 0;
    while (true)
    {
        if (!_buckets[position].valid)
        {
            if (std::is_trivially_copyable_v<value_type>)
                _buckets[position].value = std::move(insert_value);
            else
                new (&_buckets[position].value) value_type(std::move(insert_value));
            _buckets[position].valid = 1;
            _buckets[position].distance = distance;
            ++_size;
            return position;
        }
        if (distance > _buckets[position].distance)
        {
            std::swap(_buckets[position].value, insert_value);
            std::swap(_buckets[position].distance, distance);
        }
        position = (position + 1) % _capacity;
        ++distance;
    }
}

template <class TableTraits, class Hash, class Allocator>
uint32_t
nhash_table<TableTraits, Hash, Allocator>::find_position(const key_type& key) const
{
    if (_size == 0)
        return _capacity;
    uint32_t position = Hash()(key) % _capacity;
    uint16_t distance = 0;
    while (_buckets[position].valid)
    {
        if (get_key(_buckets[position].value) == key)
            return position;
        if (distance > _buckets[position].distance)
            break;
        position = (position + 1) % _capacity;
        ++distance;
    };
    return _capacity;
}

template <class TableTraits, class Hash, class Allocator>
template <class ValueType>
NTR_INLINE void
nhash_table<TableTraits, Hash, Allocator>::forward_insert(ValueType&& value)
{
    uint32_t position = find_position(get_key(value));
    if (position == _capacity)
    {
        if constexpr (std::is_rvalue_reference_v<ValueType>)
            insert_force(std::forward<ValueType>(value));
        else
        {
            value_type value_copy(std::forward<ValueType>(value));
            insert_force(std::move(value_copy));
        }
    }
}

} // namespace ntr