//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "../type/ntype.hpp"

namespace ntr
{

struct bucket_info
{
    uint16_t valid;
    uint16_t distance;
};

constexpr NTR_INLINE size_t bucket_size(size_t item_size);
NTR_INLINE void* bucket_pp(void* _bucket, size_t item_size);
NTR_INLINE void* get_item(void* _bucket);
NTR_INLINE void* get_bucket(void* buckets, uint32_t position, size_t item_size);

class NTR_API ntable
{
public:
    NTR_INLINE uint32_t size() const { return _size; };
    NTR_INLINE bool empty() const { return _size == 0; };

protected:
    using get_key_function = void* (*)(void*);
    using hash_function = uint32_t (*)(void*);
    using key_equal_function = bool (*)(void*, void*);

    ntable();
    void copy_init(const ntable& other, size_t item_size, ntype::operations* ops);
    void move_init(ntable&& other);
    void destruct(size_t item_size, ntype::operations* ops);

    void reserve(uint32_t new_capacity, size_t item_size, hash_function hash,
                 get_key_function get_key, ntype::operations* ops);
    void insert(void* item_data, size_t item_size, hash_function hash,
                get_key_function get_key, key_equal_function key_equal,
                ntype::operations* ops, bool is_move);
    uint32_t insert_force(void* item_data, size_t item_size, hash_function hash,
                          get_key_function get_key, ntype::operations* ops, bool is_move);
    bool remove(void* key_data, size_t item_size, hash_function hash,
                get_key_function get_key, key_equal_function key_equal,
                ntype::operations* ops);
    void clear(size_t item_size, ntype::operations* ops);
    bool contains(void* key_data, size_t item_size, hash_function hash,
                  get_key_function get_key, key_equal_function key_equal) const;
    uint32_t find_position(void* key_data, size_t item_size, hash_function hash,
                           get_key_function get_key, key_equal_function key_equal) const;
    void* find(void* key_data, size_t item_size, hash_function hash,
               get_key_function get_key, key_equal_function key_equal) const;
    void* begin(size_t item_size) const;
    void* end(size_t item_size) const;

    uint32_t _size;
    uint32_t _capacity;
    void* _buckets;
};

template <class T>
struct table_iterator
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    table_iterator(void* bucket, void* end);
    NTR_INLINE table_iterator& operator++();
    NTR_INLINE table_iterator operator++(int);
    NTR_INLINE bool operator==(const table_iterator& other) const;
    NTR_INLINE bool operator!=(const table_iterator& other) const;
    NTR_INLINE reference operator*() const;
    NTR_INLINE pointer operator->() const;

private:
    void* _bucket;
    void* _end;
};

template <class Value>
struct table_set_traits
{
    using key_type = Value;
    using value_type = Value;
    using item_type = Value;
    static constexpr auto get_key = [](void* item_data) -> void*
    {
        return static_cast<key_type*>(item_data);
    };
};

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

template <class TableTraits, class Hash = std::hash<typename TableTraits::key_type>>
class nhash_table : public ntable
{
public:
    using key_type = typename TableTraits::key_type;
    using value_type = typename TableTraits::value_type;
    using item_type = typename TableTraits::item_type;
    using iterator = table_iterator<item_type>;
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

template <class Value, class Hash = std::hash<Value>>
class nhash_set : public nhash_table<table_set_traits<Value>, Hash>
{
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

#include "../impl/tool/ntable.inl"