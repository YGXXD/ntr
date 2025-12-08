//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "nhash_table.hpp"

namespace ntr
{

template <class Key, class Value>
struct table_map_traits
{
    using key_type = Key;
    using value_type = Value;
    using item_type = std::pair<Key, Value>;
    static constexpr auto get_key = [](void* item_data) -> void*
    {
        return &static_cast<item_type*>(item_data)->first;
    };
};

template <class Key, class Value, class Hash = std::hash<Key>>
class nhash_map : public nhash_table<table_map_traits<Key, Value>, Hash>
{
    using hash_table_type = nhash_table<table_map_traits<Key, Value>, Hash>;
    using hash_table_type::hash_table_type;
    using typename hash_table_type::item_type;
    using typename hash_table_type::key_type;
    using typename hash_table_type::value_type;
    static constexpr size_t item_size = sizeof(item_type);

    static_assert(std::is_same_v<Key, key_type>);
    static_assert(std::is_same_v<Value, value_type>);

    using hash_table_type::_buckets;
    using hash_table_type::_capacity;
    using hash_table_type::get_key;
    using hash_table_type::hash;
    using hash_table_type::key_equal;

public:
    using hash_table_type::insert;
    NTR_INLINE void insert(const key_type& key, const value_type& value);
    NTR_INLINE void insert(const key_type& key, value_type&& value);
    NTR_INLINE value_type& at(const key_type& key);
    NTR_INLINE const value_type& at(const key_type& key) const;
    NTR_INLINE value_type& operator[](const key_type& key);
    NTR_INLINE const value_type& operator[](const key_type& key) const;
};

} // namespace ntr

#include "../impl/tool/nhash_map.inl"