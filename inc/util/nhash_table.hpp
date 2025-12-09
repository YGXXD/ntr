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
struct nhash_table_bucket
{
    uint16_t valid;
    uint16_t distance;
    T element;
};

template <class T>
struct nhash_table_iterator
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    nhash_table_iterator(nhash_table_bucket<value_type>* bucket,
                         nhash_table_bucket<value_type>* end);
    NTR_INLINE nhash_table_iterator& operator++();
    NTR_INLINE nhash_table_iterator operator++(int);
    NTR_INLINE bool operator==(const nhash_table_iterator& other) const;
    NTR_INLINE bool operator!=(const nhash_table_iterator& other) const;
    NTR_INLINE reference operator*() const;
    NTR_INLINE pointer operator->() const;

private:
    nhash_table_bucket<value_type>* _bucket;
    nhash_table_bucket<value_type>* _end;
};

template <class TableTraits, class Hash = std::hash<typename TableTraits::key_type>,
          class Allocator =
              std::allocator<nhash_table_bucket<typename TableTraits::elem_type>>>
class nhash_table
{
public:
    using key_type = typename TableTraits::key_type;
    using value_type = typename TableTraits::value_type;
    using element_type = typename TableTraits::element_type;
    using bucket_type = nhash_table_bucket<element_type>;
    using iterator = nhash_table_iterator<element_type>;
    static constexpr auto get_key = TableTraits::get_key;

public:
    nhash_table();
    nhash_table(const nhash_table& other);
    nhash_table(nhash_table&& other);
    ~nhash_table();

    NTR_INLINE void reserve(uint32_t new_capacity);
    NTR_INLINE void insert(const element_type& element);
    NTR_INLINE void insert(element_type&& element);
    NTR_INLINE bool remove(const key_type& key);
    NTR_INLINE bool remove(const iterator& it);
    NTR_INLINE bool contains(const key_type& key) const;
    NTR_INLINE void clear();
    NTR_INLINE uint32_t size() const;;
    NTR_INLINE bool empty() const;;
    NTR_INLINE iterator find(const key_type& key) const;
    NTR_INLINE iterator begin() const;
    NTR_INLINE iterator end() const;

protected:
    NTR_INLINE uint32_t insert_force(element_type&& insert_element);
    NTR_INLINE uint32_t find_position(const key_type& key) const;

    uint32_t _size;
    uint32_t _capacity;
    bucket_type* _buckets;
};

} // namespace ntr

#include "../impl/util/nhash_table.inl"