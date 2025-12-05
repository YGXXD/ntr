//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../tool/narray.hpp"
#include "../../tool/ntraits.hpp"

namespace ntr
{

template <typename T>
array_iterator<T>::array_iterator(void* item) : _item(item) {};

template <typename T>
NTR_INLINE array_iterator<T>& array_iterator<T>::operator++()
{
    _item = static_cast<char*>(_item) + sizeof(T);
    return *this;
}

template <typename T>
NTR_INLINE array_iterator<T> array_iterator<T>::operator++(int)
{
    array_iterator temp = *this;
    ++*this;
    return temp;
}

template <typename T>
NTR_INLINE bool array_iterator<T>::operator==(const array_iterator& other) const
{
    return _item == other._item;
}

template <typename T>
NTR_INLINE bool array_iterator<T>::operator!=(const array_iterator& other) const
{
    return _item != other._item;
}

template <typename T>
NTR_INLINE T& array_iterator<T>::operator*()
{
    return *static_cast<T*>(_item);
}

template <typename T>
NTR_INLINE const T& array_iterator<T>::operator*() const
{
    return *static_cast<const T*>(_item);
}

template <typename T>
NTR_INLINE T* array_iterator<T>::operator->()
{
    return static_cast<T*>(_item);
}

template <typename T>
NTR_INLINE const T* array_iterator<T>::operator->() const
{
    return static_cast<const T*>(_item);
}

template <class Value>
nvector<Value>::nvector() : narray()
{
}

template <class Value>
nvector<Value>::nvector(const nvector& other)
{
    copy_init(other, item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
nvector<Value>::nvector(nvector&& other)
{
    move_init(std::move(other));
}

template <class Value>
nvector<Value>::nvector(std::initializer_list<Value> list)
{
    reserve(list.size());
    for (auto& item : list)
        push_back(item);
}

template <class Value>
nvector<Value>::~nvector()
{
    destruct(item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
NTR_INLINE void nvector<Value>::reserve(uint32_t new_capacity)
{
    narray::reserve(new_capacity, item_size,
                    &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
NTR_INLINE void nvector<Value>::push_back(const item_type& item)
{
    narray::push_back(const_cast<item_type*>(&item), item_size,
                      &ntype_ops_traits<item_type>::instance().ops, false);
}
template <class Value>
NTR_INLINE void nvector<Value>::push_back(item_type&& item)
{
    narray::push_back(&item, item_size, &ntype_ops_traits<item_type>::instance().ops,
                      true);
}

template <class Value>
NTR_INLINE void nvector<Value>::pop_back()
{
    narray::pop_back(item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
NTR_INLINE void nvector<Value>::insert(const item_type& item, uint32_t index)
{
    narray::insert(const_cast<item_type*>(&item), item_size, index,
                   &ntype_ops_traits<item_type>::instance().ops, false);
}
template <class Value>
NTR_INLINE void nvector<Value>::insert(item_type&& item, uint32_t index)
{
    narray::insert(&item, item_size, index, &ntype_ops_traits<item_type>::instance().ops,
                   true);
}

template <class Value>
NTR_INLINE void nvector<Value>::remove(uint32_t index)
{
    narray::remove(item_size, index, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
NTR_INLINE void nvector<Value>::remove(const iterator& it)
{
    narray::remove(item_size, &(*it) - static_cast<Value*>(_datas),
                   &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
NTR_INLINE void nvector<Value>::clear()
{
    narray::clear(item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
NTR_INLINE typename nvector<Value>::iterator nvector<Value>::begin() const
{
    return iterator(narray::begin());
}

template <class Value>
NTR_INLINE typename nvector<Value>::iterator nvector<Value>::end() const
{
    return iterator(narray::end(item_size));
}

template <class Value>
NTR_INLINE Value& nvector<Value>::at(uint32_t index)
{
    if (index >= _size)
        throw std::out_of_range("nvector<Value>::at : invalid index");
    return *reinterpret_cast<Value*>(static_cast<char*>(_datas) + item_size * index);
}

template <class Value>
NTR_INLINE const Value& nvector<Value>::at(uint32_t index) const
{
    if (index >= _size)
        throw std::out_of_range("nvector<Value>::at : invalid index");
    return *reinterpret_cast<const Value*>(static_cast<const char*>(_datas) +
                                           item_size * index);
}

template <class Value>
NTR_INLINE Value& nvector<Value>::operator[](uint32_t index)
{
    return *reinterpret_cast<Value*>(static_cast<char*>(_datas) + item_size * index);
}

template <class Value>
NTR_INLINE const Value& nvector<Value>::operator[](uint32_t index) const
{
    return *reinterpret_cast<const Value*>(static_cast<const char*>(_datas) +
                                           item_size * index);
}

} // namespace ntr