//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "ntable.hpp"

namespace ntr
{

template <class T>
struct nhash_table_iterator
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    nhash_table_iterator(void* bucket, void* end);
    NTR_INLINE nhash_table_iterator& operator++();
    NTR_INLINE nhash_table_iterator operator++(int);
    NTR_INLINE bool operator==(const nhash_table_iterator& other) const;
    NTR_INLINE bool operator!=(const nhash_table_iterator& other) const;
    NTR_INLINE reference operator*() const;
    NTR_INLINE pointer operator->() const;

private:
    void* _bucket;
    void* _end;
};

template <class TableTraits, class Hash = std::hash<typename TableTraits::key_type>>
class nhash_table : public ntable
{
public:
    using key_type = typename TableTraits::key_type;
    using value_type = typename TableTraits::value_type;
    using item_type = typename TableTraits::item_type;
    using iterator = nhash_table_iterator<item_type>;
    static constexpr size_t item_size = sizeof(item_type);

protected:
    static constexpr auto get_key = TableTraits::get_key;
    static constexpr auto hash = [](void* key_data) -> uint32_t
    {
        return Hash()(*static_cast<key_type*>(key_data));
    };
    static constexpr auto key_equal = [](void* key_data1, void* key_data2) -> bool
    {
        return *static_cast<key_type*>(key_data1) == *static_cast<key_type*>(key_data2);
    };

public:
    nhash_table();
    nhash_table(const nhash_table& other);
    nhash_table(nhash_table&& other);
    ~nhash_table();

    NTR_INLINE void reserve(uint32_t new_capacity);
    NTR_INLINE void insert(const item_type& item);
    NTR_INLINE void insert(item_type&& item);
    NTR_INLINE bool remove(const key_type& key);
    NTR_INLINE bool remove(key_type&& key);
    NTR_INLINE bool remove(const iterator& it);
    NTR_INLINE bool contains(const key_type& key) const;
    NTR_INLINE bool contains(key_type&& key) const;
    NTR_INLINE void clear();
    NTR_INLINE iterator find(const key_type& key) const;
    NTR_INLINE iterator find(key_type&& key) const;
    NTR_INLINE iterator begin() const;
    NTR_INLINE iterator end() const;
};

} // namespace ntr

#include "../impl/tool/nhash_table.inl"