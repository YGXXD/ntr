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

constexpr NTR_INLINE size_t bucket_size(size_t item_size)
{
    return sizeof(bucket_info) + item_size;
}

NTR_INLINE void* bucket_pp(void* _bucket, size_t item_size)
{
    return static_cast<char*>(_bucket) + bucket_size(item_size);
}

NTR_INLINE void* get_item(void* _bucket)
{
    return static_cast<char*>(_bucket) + sizeof(bucket_info);
}

NTR_INLINE void* get_bucket(void* buckets, uint32_t position, size_t item_size)
{
    return static_cast<char*>(buckets) + position * bucket_size(item_size);
}

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

} // namespace ntr