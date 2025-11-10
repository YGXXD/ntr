//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "type/ntype.hpp"

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
    NTR_INLINE uint32_t size() const { return size(); };
    NTR_INLINE bool empty() const { return _size == 0; };

protected:
    using hash_function = uint32_t (*)(void*);
    using get_key_function = void* (*)(void*);
    using key_equal_function = bool (*)(void*, void*);
    using update_value_function = void (*)(void*, void*);

    ntable();
    void copy_init(const ntable& other, size_t item_size, ntype::operations* ops);
    void move_init(ntable&& other);
    void destruct(size_t item_size, ntype::operations* ops);

    void reserve(uint32_t new_capacity, size_t item_size, hash_function hash,
                 get_key_function get_key);
    void insert(void* item_data, size_t item_size, hash_function hash,
                get_key_function get_key, key_equal_function key_equal,
                int construct_type, ntype::operations* ops,
                update_value_function update_value);
    uint32_t insert_force(void* item_data, size_t item_size, hash_function hash,
                          get_key_function get_key, int construct_type,
                          ntype::operations* ops);
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
    table_iterator(void* bucket, void* end);
    NTR_INLINE table_iterator& operator++();
    NTR_INLINE table_iterator operator++(int);
    NTR_INLINE bool operator==(const table_iterator& other) const;
    NTR_INLINE bool operator!=(const table_iterator& other) const;
    NTR_INLINE T& operator*();
    NTR_INLINE const T& operator*() const;
    NTR_INLINE T* operator->();
    NTR_INLINE const T* operator->() const;

private:
    void* _bucket;
    void* _end;
};

template <class Key, class Value, class Hash = std::hash<Key>>
class nhash_map : public ntable
{
public:
    using item_type = std::pair<Key, Value>;
    using iterator = table_iterator<item_type>;
    static constexpr size_t item_size = sizeof(item_type);

private:
    static constexpr auto hash = [](void* key_data) -> uint32_t
    {
        return Hash()(*static_cast<Key*>(key_data));
    };

    static constexpr auto get_key = [](void* item_data) -> void*
    {
        return &static_cast<item_type*>(item_data)->first;
    };

    static constexpr auto key_equal = [](void* key_data1, void* key_data2) -> bool
    {
        return *static_cast<Key*>(key_data1) == *static_cast<Key*>(key_data2);
    };

    static constexpr auto update_value = [](void* item_data, void* value_data)
    {
        static_cast<item_type*>(item_data)->second =
            static_cast<item_type*>(value_data)->second;
    };

public:
    nhash_map();
    nhash_map(const nhash_map& other);
    nhash_map(nhash_map&& other);
    ~nhash_map();

    NTR_INLINE void reserve(uint32_t new_capacity);
    NTR_INLINE void insert(const item_type& item);
    NTR_INLINE void insert(item_type&& item);
    NTR_INLINE void insert(const Key& key, const Value& value);
    NTR_INLINE void insert(const Key& key, Value&& value);
    NTR_INLINE bool remove(const Key& key);
    NTR_INLINE bool remove(Key&& key);
    NTR_INLINE bool remove(const iterator& it);
    NTR_INLINE bool contains(const Key& key) const;
    NTR_INLINE bool contains(Key&& key) const;
    NTR_INLINE iterator find(const Key& key) const;
    NTR_INLINE iterator find(Key&& key) const;
    NTR_INLINE iterator begin() const;
    NTR_INLINE iterator end() const;
    NTR_INLINE Value& operator[](const Key& key);
    NTR_INLINE const Value& operator[](const Key& key) const;
};

} // namespace ntr

#include "../impl/tool/ntable.inl"