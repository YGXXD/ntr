//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../tool/nvector.hpp"
#include "../../tool/ntraits.hpp"

namespace ntr
{

template <typename T>
nvector_iterator<T>::nvector_iterator(void* item) : _item(item) {};

template <typename T>
NTR_INLINE nvector_iterator<T>& nvector_iterator<T>::operator++()
{
    _item = static_cast<value_type*>(_item) + 1;
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
    _item = static_cast<value_type*>(_item) - 1;
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
    return nvector_iterator(static_cast<value_type*>(_item) + offset);
}

template <typename T>
NTR_INLINE nvector_iterator<T>& nvector_iterator<T>::operator+=(difference_type offset)
{
    _item = static_cast<value_type*>(_item) + offset;
    return *this;
}

template <typename T>
NTR_INLINE nvector_iterator<T>
nvector_iterator<T>::operator-(difference_type offset) const
{
    return nvector_iterator(static_cast<value_type*>(_item) - offset);
}

template <typename T>
NTR_INLINE typename nvector_iterator<T>::difference_type
nvector_iterator<T>::operator-(const nvector_iterator& other) const
{
    return static_cast<value_type*>(_item) - static_cast<value_type*>(other._item);
}

template <typename T>
NTR_INLINE nvector_iterator<T>& nvector_iterator<T>::operator-=(difference_type offset)
{
    _item = static_cast<value_type*>(_item) - offset;
    return *this;
}

template <typename T>
NTR_INLINE bool nvector_iterator<T>::operator==(const nvector_iterator& other) const
{
    return _item == other._item;
}

template <typename T>
NTR_INLINE bool nvector_iterator<T>::operator!=(const nvector_iterator& other) const
{
    return _item != other._item;
}

template <typename T>
NTR_INLINE typename nvector_iterator<T>::reference nvector_iterator<T>::operator*() const
{
    return *static_cast<T*>(_item);
}

template <typename T>
NTR_INLINE typename nvector_iterator<T>::pointer nvector_iterator<T>::operator->() const
{
    return static_cast<T*>(_item);
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
NTR_INLINE void nvector<Value>::insert(uint32_t index, const item_type& item)
{
    narray::insert(index, const_cast<item_type*>(&item), item_size,
                   &ntype_ops_traits<item_type>::instance().ops, false);
}
template <class Value>
NTR_INLINE void nvector<Value>::insert(uint32_t index, item_type&& item)
{
    narray::insert(index, &item, item_size, &ntype_ops_traits<item_type>::instance().ops,
                   true);
}

template <class Value>
NTR_INLINE void nvector<Value>::remove(uint32_t index)
{
    narray::remove(index, item_size, &ntype_ops_traits<item_type>::instance().ops);
}

template <class Value>
NTR_INLINE void nvector<Value>::remove(const iterator& it)
{
    narray::remove(&(*it) - static_cast<Value*>(_datas), item_size,
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
NTR_INLINE typename nvector<Value>::item_type& nvector<Value>::at(uint32_t index)
{
    if (index >= _size)
        throw std::out_of_range("nvector<Value>::at : invalid index");
    return *(static_cast<Value*>(_datas) + index);
}

template <class Value>
NTR_INLINE const typename nvector<Value>::item_type&
nvector<Value>::at(uint32_t index) const
{
    if (index >= _size)
        throw std::out_of_range("nvector<Value>::at : invalid index");
    return *(static_cast<const Value*>(_datas) + index);
}

template <class Value>
NTR_INLINE typename nvector<Value>::item_type& nvector<Value>::operator[](uint32_t index)
{
    return *(static_cast<Value*>(_datas) + index);
}

template <class Value>
NTR_INLINE const typename nvector<Value>::item_type&
nvector<Value>::operator[](uint32_t index) const
{
    return *(static_cast<const Value*>(_datas) + index);
}

} // namespace ntr