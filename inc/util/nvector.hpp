//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"

namespace ntr
{

template <class T>
struct nvector_iterator
{
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    nvector_iterator(value_type* value);
    NTR_INLINE nvector_iterator& operator++();
    NTR_INLINE nvector_iterator operator++(int);
    NTR_INLINE nvector_iterator& operator--();
    NTR_INLINE nvector_iterator operator--(int);
    NTR_INLINE nvector_iterator operator+(difference_type offset) const;
    NTR_INLINE nvector_iterator& operator+=(difference_type offset);
    NTR_INLINE nvector_iterator operator-(difference_type offset) const;
    NTR_INLINE nvector_iterator& operator-=(difference_type offset);
    NTR_INLINE difference_type operator-(const nvector_iterator& other) const;
    NTR_INLINE bool operator==(const nvector_iterator& other) const;
    NTR_INLINE bool operator!=(const nvector_iterator& other) const;
    NTR_INLINE reference operator*() const;
    NTR_INLINE pointer operator->() const;

private:
    value_type* _value;
};

template <class Value, class Allocator = std::allocator<Value>>
class nvector
{
public:
    using element_type = Value;
    using iterator = nvector_iterator<element_type>;

    nvector();
    nvector(const nvector& other);
    nvector(nvector&& other);
    nvector(std::initializer_list<element_type> list);
    ~nvector();

    void reserve(uint32_t new_capacity);
    NTR_INLINE void push_back(const element_type& value);
    NTR_INLINE void push_back(element_type&& value);
    NTR_INLINE void pop_back();
    NTR_INLINE void insert(uint32_t index, const element_type& value);
    void insert(uint32_t index, element_type&& value);
    void remove(uint32_t index);
    NTR_INLINE void remove(const iterator& it);
    NTR_INLINE void clear();
    NTR_INLINE uint32_t size() const;
    NTR_INLINE bool empty() const;
    NTR_INLINE element_type* data();
    NTR_INLINE const element_type* data() const;
    NTR_INLINE element_type& at(uint32_t index);
    NTR_INLINE const element_type& at(uint32_t index) const;
    NTR_INLINE element_type& operator[](uint32_t index);
    NTR_INLINE const element_type& operator[](uint32_t index) const;
    NTR_INLINE iterator begin() const;
    NTR_INLINE iterator end() const;

private:
    uint32_t _size;
    uint32_t _capacity;
    element_type* _datas;
};

} // namespace ntr

#include "../impl/util/nvector.inl"