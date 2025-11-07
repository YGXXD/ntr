//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "core/ntable.hpp"

namespace ntr
{

ntable::ntable() : _size(0), _capacity(0), _buckets(nullptr)
{
}

void ntable::copy_init(const ntable& other, size_t item_size, ntype::operations* ops)
{
    _size = other._size;
    _capacity = other._capacity;
    _buckets = nullptr;

    if (_capacity > 0)
    {
        const size_t alloc_size = bucket_size(item_size) * _capacity;
        _buckets = malloc(alloc_size);
        memset(_buckets, 0, alloc_size);
        for (uint32_t i = 0; i < _capacity; ++i)
        {
            bucket_info* other_binfo =
                static_cast<bucket_info*>(get_bucket(other._buckets, i, item_size));
            bucket_info* binfo =
                static_cast<bucket_info*>(get_bucket(_buckets, i, item_size));
            if (other_binfo->valid)
            {
                binfo->valid = other_binfo->valid;
                binfo->distance = other_binfo->distance;
                ops->copy_construct(get_item(binfo), get_item(other_binfo));
            }
        }
    }
}

void ntable::move_init(ntable&& other)
{
    _size = other._size;
    _capacity = other._capacity;
    _buckets = other._buckets;
    other._size = 0;
    other._capacity = 0;
    other._buckets = nullptr;
}

void ntable::destruct(size_t item_size, ntype::operations* ops)
{
    for (uint32_t i = 0; i < _capacity; ++i)
    {
        bucket_info* binfo =
            static_cast<bucket_info*>(get_bucket(_buckets, i, item_size));
        if (binfo->valid)
            ops->destruct(get_item(binfo));
    }

    if (_buckets)
        free(_buckets);
}

void ntable::reserve(uint32_t new_capacity, size_t item_size, hash_function hash,
                     get_key_function get_key)
{
    void* old_buckets = _buckets;
    uint32_t old_capacity = _capacity;
    _capacity = new_capacity;
    _size = 0;
    const size_t alloc_size = bucket_size(item_size) * new_capacity;
    _buckets = malloc(alloc_size);
    memset(_buckets, 0, alloc_size);
    for (uint32_t i = 0; i < old_capacity; ++i)
    {
        bucket_info* old_binfo =
            static_cast<bucket_info*>(get_bucket(old_buckets, i, item_size));
        if (old_binfo->valid)
        {
            insert_force(get_item(old_binfo), item_size, hash, get_key, 2, nullptr);
        }
    }
    free(old_buckets);
}

void ntable::insert(void* item_data, size_t item_size, hash_function hash,
                    get_key_function get_key, key_equal_function key_equal,
                    int construct_type, ntype::operations* ops,
                    update_value_function update_value)
{
    uint32_t position =
        find_position(get_key(item_data), item_size, hash, get_key, key_equal);
    if (position == _capacity)
    {
        insert_force(item_data, item_size, hash, get_key, construct_type, ops);
    }
    else if (update_value)
    {
        update_value(get_item(get_bucket(_buckets, position, item_size)), item_data);
    }
}

uint32_t ntable::insert_force(void* item_data, size_t item_size, hash_function hash,
                              get_key_function get_key, int construct_type,
                              ntype::operations* ops)
{
    if (_size >= _capacity * 3 / 4)
        reserve((_capacity == 0 ? 32 : _capacity * 2), item_size, hash, get_key);
    uint32_t position = hash(get_key(item_data)) % _capacity;
    uint16_t distance = 0;
    char* insert_item = static_cast<char*>(std::malloc(item_size));
    switch (construct_type)
    {
    case 0:
        ops->copy_construct(insert_item, item_data);
        break;
    case 1:
        ops->move_construct(insert_item, item_data);
        break;
    case 2:
        memcpy(insert_item, item_data, item_size);
        break;
    default:
        throw std::invalid_argument("nhash_map::insert : insert construct type error");
        break;
    }
    while (true)
    {
        bucket_info* binfo =
            static_cast<bucket_info*>(get_bucket(_buckets, position, item_size));
        void* bitem = get_item(binfo);
        if (!binfo->valid)
        {
            memcpy(bitem, insert_item, item_size);
            binfo->valid = 1;
            binfo->distance = distance;
            ++_size;
            std::free(insert_item);
            return position;
        }
        if (distance > binfo->distance)
        {
            std::swap_ranges(static_cast<char*>(bitem),
                             static_cast<char*>(bitem) + item_size, insert_item);
            std::swap(binfo->distance, distance);
        }
        position = (position + 1) % _capacity;
        ++distance;
    }
}

bool ntable::remove(void* key_data, size_t item_size, hash_function hash,
                    get_key_function get_key, key_equal_function key_equal,
                    ntype::operations* ops)
{
    uint32_t position = find_position(key_data, item_size, hash, get_key, key_equal);
    if (position != _capacity)
    {
        bucket_info* binfo =
            static_cast<bucket_info*>(get_bucket(_buckets, position, item_size));
        binfo->valid = 0;
        binfo->distance = 0;
        ops->destruct(get_item(binfo));
        --_size;

        uint32_t next_position = (position + 1) % _capacity;
        bucket_info* next_binfo =
            static_cast<bucket_info*>(get_bucket(_buckets, next_position, item_size));
        while (next_binfo->valid && next_binfo->distance > 0)
        {
            std::swap_ranges(reinterpret_cast<char*>(binfo),
                             reinterpret_cast<char*>(binfo) + bucket_size(item_size),
                             reinterpret_cast<char*>(next_binfo));
            --binfo->distance;
            position = next_position;
            next_position = (next_position + 1) % _capacity;
        }
        return true;
    }
    return false;
}

void ntable::clear(size_t item_size, ntype::operations* ops)
{
    for (uint32_t i = 0; i < _capacity; ++i)
    {
        bucket_info* binfo =
            static_cast<bucket_info*>(get_bucket(_buckets, i, item_size));
        if (binfo->valid)
        {
            binfo->valid = 0;
            binfo->distance = 0;
            ops->destruct(get_item(binfo));
        }
    }
    _size = 0;
}

bool ntable::contains(void* key_data, size_t item_size, hash_function hash,
                      get_key_function get_key, key_equal_function key_equal) const
{
    return find_position(key_data, item_size, hash, get_key, key_equal) != _capacity;
}

uint32_t ntable::find_position(void* key_data, size_t item_size, hash_function hash,
                               get_key_function get_key,
                               key_equal_function key_equal) const
{
    if (_capacity == 0)
        return _capacity;
    uint32_t position = hash(key_data) % _capacity;
    uint32_t distance = 0;
    bucket_info* binfo =
        static_cast<bucket_info*>(get_bucket(_buckets, position, item_size));
    while (binfo->valid)
    {
        if (key_equal(key_data, get_key(get_item(binfo))))
            return position;
        if (distance > binfo->distance)
            break;
        position = (position + 1) % _capacity;
        binfo = static_cast<bucket_info*>(get_bucket(_buckets, position, item_size));
        ++distance;
    };
    return _capacity;
}

void* ntable::find(void* key_data, size_t item_size, hash_function hash,
                   get_key_function get_key, key_equal_function key_equal) const
{
    uint32_t position = find_position(key_data, item_size, hash, get_key, key_equal);
    return get_bucket(_buckets, position, item_size);
}

void* ntable::begin(size_t item_size) const
{
    void* bucket = _buckets;
    void* end = get_bucket(_buckets, _capacity, item_size);
    for (; bucket != end; bucket = bucket_pp(bucket, item_size))
    {
        if (static_cast<bucket_info*>(bucket)->valid)
            break;
    }
    return bucket;
}

void* ntable::end(size_t item_size) const
{
    return get_bucket(_buckets, _capacity, item_size);
}

} // namespace ntr