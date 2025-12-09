//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../tool/nvector.hpp"

namespace ntr
{

template <typename T>
nvector_iterator<T>::nvector_iterator(value_type* value) : _value(value) {};

template <typename T>
NTR_INLINE nvector_iterator<T>& nvector_iterator<T>::operator++()
{
    _value = static_cast<value_type*>(_value) + 1;
    return *this;
}

template <typename T>
NTR_INLINE nvector_iterator<T> nvector_iterator<T>::operator++(int)
{
    nvector_iterator temp = *this;
    ++*this;
    return temp;
}

template <typename T>
NTR_INLINE nvector_iterator<T>& nvector_iterator<T>::operator--()
{
    _value = static_cast<value_type*>(_value) - 1;
    return *this;
}

template <typename T>
NTR_INLINE nvector_iterator<T> nvector_iterator<T>::operator--(int)
{
    nvector_iterator temp = *this;
    --*this;
    return temp;
}

template <typename T>
NTR_INLINE nvector_iterator<T>
nvector_iterator<T>::operator+(difference_type offset) const
{
    return nvector_iterator(static_cast<value_type*>(_value) + offset);
}

template <typename T>
NTR_INLINE nvector_iterator<T>& nvector_iterator<T>::operator+=(difference_type offset)
{
    _value = static_cast<value_type*>(_value) + offset;
    return *this;
}

template <typename T>
NTR_INLINE nvector_iterator<T>
nvector_iterator<T>::operator-(difference_type offset) const
{
    return nvector_iterator(static_cast<value_type*>(_value) - offset);
}

template <typename T>
NTR_INLINE typename nvector_iterator<T>::difference_type
nvector_iterator<T>::operator-(const nvector_iterator& other) const
{
    return static_cast<value_type*>(_value) - static_cast<value_type*>(other._value);
}

template <typename T>
NTR_INLINE nvector_iterator<T>& nvector_iterator<T>::operator-=(difference_type offset)
{
    _value = static_cast<value_type*>(_value) - offset;
    return *this;
}

template <typename T>
NTR_INLINE bool nvector_iterator<T>::operator==(const nvector_iterator& other) const
{
    return _value == other._value;
}

template <typename T>
NTR_INLINE bool nvector_iterator<T>::operator!=(const nvector_iterator& other) const
{
    return _value != other._value;
}

template <typename T>
NTR_INLINE typename nvector_iterator<T>::reference nvector_iterator<T>::operator*() const
{
    return *static_cast<T*>(_value);
}

template <typename T>
NTR_INLINE typename nvector_iterator<T>::pointer nvector_iterator<T>::operator->() const
{
    return static_cast<T*>(_value);
}

NTR_INLINE uint32_t nvector_growth_capacity(uint32_t capacity)
{
    if (capacity == 0)
        return 16;
    if (capacity < 1024)
        return capacity * 2;
    return capacity + capacity / 2;
}

template <class Value, class Allocator>
nvector<Value, Allocator>::nvector() : _size(0), _capacity(0), _datas(nullptr)
{
}

template <class Value, class Allocator>
nvector<Value, Allocator>::nvector(const nvector& other)
    : _size(other._size), _capacity(other._capacity), _datas(nullptr)
{
    if (_capacity > 0)
        _datas = Allocator().allocate(_capacity);
    if (_size > 0)
    {
        if constexpr (std::is_trivially_copyable_v<value_type>)
            std::memcpy(_datas, other._datas, _size * sizeof(value_type));
        else
            std::uninitialized_copy_n(other._datas, _size, _datas);
    }
}

template <class Value, class Allocator>
nvector<Value, Allocator>::nvector(nvector&& other)
    : _size(other._size), _capacity(other._capacity), _datas(other._datas)
{
    other._size = 0;
    other._capacity = 0;
    other._datas = nullptr;
}

template <class Value, class Allocator>
nvector<Value, Allocator>::nvector(std::initializer_list<Value> list)
    : _size(0), _capacity(0), _datas(nullptr)
{
    reserve(list.size());
    for (auto& value : list)
        push_back(value);
}

template <class Value, class Allocator>
nvector<Value, Allocator>::~nvector()
{
    clear();
    if (_datas)
        Allocator().deallocate(_datas, _capacity);
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::reserve(uint32_t new_capacity)
{
    if (new_capacity <= _capacity)
        return;

    Allocator allocator {};
    value_type* new_datas = allocator.allocate(new_capacity);
    if (_datas)
    {
        if constexpr (std::is_trivially_copyable_v<value_type>)
            std::memcpy(new_datas, _datas, _size * sizeof(value_type));
        else
        {
            std::uninitialized_move_n(_datas, _size, new_datas);
            std::destroy_n(_datas, _size);
        }
        allocator.deallocate(_datas, _capacity);
    }
    _datas = new_datas;
    _capacity = new_capacity;
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::push_back(const value_type& value)
{
    push_back(value_type(value));
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::push_back(value_type&& value)
{
    if (_size >= _capacity)
        reserve(nvector_growth_capacity(_capacity));
    if constexpr (std::is_trivially_copyable_v<value_type>)
        _datas[_size++] = std::move(value);
    else
        new (&_datas[_size++]) value_type(std::move(value));
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::pop_back()
{
    if (_size > 0)
    {
        if constexpr (std::is_trivially_copyable_v<value_type>)
            --_size;
        else
            _datas[--_size].~value_type();
    }
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::insert(uint32_t index, const value_type& value)
{
    insert(index, value_type(value));
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::insert(uint32_t index, value_type&& value)
{
    if (index >= _size)
    {
        push_back(std::move(value));
        return;
    }
    if (_size >= _capacity)
        reserve(nvector_growth_capacity(_capacity));
    if constexpr (std::is_trivially_copyable_v<value_type>)
    {
        std::memmove(_datas + index + 1, _datas + index,
                     (_size - index) * sizeof(value_type));
        _datas[index] = std::move(value);
    }
    else
    {
        new (&_datas[_size]) value_type(std::move(_datas[_size - 1]));
        std::move_backward(_datas + index, _datas + _size - 1, _datas + _size);
        _datas[index].~value_type();
        new (&_datas[index]) value_type(std::move(value));
    }
    ++_size;
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::remove(uint32_t index)
{
    if (index >= _size)
        return;

    _datas[index].~value_type();
    if constexpr (std::is_trivially_copyable_v<value_type>)
    {
        if (index < _size - 1)
            std::memmove(_datas + index, _datas + index + 1,
                         (_size - index - 1) * sizeof(value_type));
    }
    else
    {
        if (index < _size - 1)
            std::move(_datas + index + 1, _datas + _size, _datas + index);
        _datas[_size - 1].~value_type();
    }
    --_size;
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::remove(const iterator& it)
{
    remove(&(*it) - _datas);
}

template <class Value, class Allocator>
NTR_INLINE void nvector<Value, Allocator>::clear()
{
    if (_size > 0)
    {
        if constexpr (!std::is_trivially_copyable_v<value_type>)
            std::destroy_n(_datas, _size);
        _size = 0;
    }
}

template <class Value, class Allocator>
NTR_INLINE uint32_t nvector<Value, Allocator>::size() const
{
    return _size;
}

template <class Value, class Allocator>
NTR_INLINE bool nvector<Value, Allocator>::empty() const
{
    return _size == 0;
}

template <class Value, class Allocator>
NTR_INLINE typename nvector<Value, Allocator>::value_type*
nvector<Value, Allocator>::data()
{
    return _datas;
}

template <class Value, class Allocator>
NTR_INLINE const typename nvector<Value, Allocator>::value_type*
nvector<Value, Allocator>::data() const
{
    return _datas;
}

template <class Value, class Allocator>
NTR_INLINE typename nvector<Value, Allocator>::value_type&
nvector<Value, Allocator>::at(uint32_t index)
{
    if (index >= _size)
        throw std::out_of_range("nvector<Value, Allocator>::at : invalid index");
    return _datas[index];
}

template <class Value, class Allocator>
NTR_INLINE const typename nvector<Value, Allocator>::value_type&
nvector<Value, Allocator>::at(uint32_t index) const
{
    if (index >= _size)
        throw std::out_of_range("nvector<Value, Allocator>::at : invalid index");
    return _datas[index];
}

template <class Value, class Allocator>
NTR_INLINE typename nvector<Value, Allocator>::value_type&
nvector<Value, Allocator>::operator[](uint32_t index)
{
    return _datas[index];
}

template <class Value, class Allocator>
NTR_INLINE const typename nvector<Value, Allocator>::value_type&
nvector<Value, Allocator>::operator[](uint32_t index) const
{
    return _datas[index];
}

template <class Value, class Allocator>
NTR_INLINE typename nvector<Value, Allocator>::iterator
nvector<Value, Allocator>::begin() const
{
    return iterator(_datas);
}

template <class Value, class Allocator>
NTR_INLINE typename nvector<Value, Allocator>::iterator
nvector<Value, Allocator>::end() const
{
    return iterator(_datas + _size);
}

} // namespace ntr