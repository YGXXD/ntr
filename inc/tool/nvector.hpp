//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "narray.hpp"

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

    nvector_iterator(void* _item);
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
    void* _item;
};

template <class Value>
class nvector : public narray
{
public:
    using item_type = Value;
    using iterator = nvector_iterator<item_type>;
    static constexpr size_t item_size = sizeof(item_type);

    nvector();
    nvector(const nvector& other);
    nvector(nvector&& other);
    nvector(std::initializer_list<Value> list);
    ~nvector();

    NTR_INLINE void reserve(uint32_t new_capacity);
    NTR_INLINE void push_back(const item_type& item);
    NTR_INLINE void push_back(item_type&& item);
    NTR_INLINE void pop_back();
    NTR_INLINE void insert(uint32_t index, const item_type& item);
    NTR_INLINE void insert(uint32_t index, item_type&& item);
    NTR_INLINE void remove(uint32_t index);
    NTR_INLINE void remove(const iterator& it);
    NTR_INLINE void clear();
    NTR_INLINE iterator begin() const;
    NTR_INLINE iterator end() const;
    NTR_INLINE item_type& at(uint32_t index);
    NTR_INLINE const item_type& at(uint32_t index) const;
    NTR_INLINE item_type& operator[](uint32_t index);
    NTR_INLINE const item_type& operator[](uint32_t index) const;
};

} // namespace ntr

#include "../impl/tool/nvector.inl"