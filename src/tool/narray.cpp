//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "tool/narray.hpp"

namespace ntr
{

NTR_INLINE uint32_t narray_growth_capacity(uint32_t capacity)
{
    return capacity == 0 ? 16 : capacity * 2;
}

narray::narray() : _size(0), _capacity(0), _datas(nullptr)
{
}

void narray::copy_init(const narray& other, size_t item_size, ntype::operations* ops)
{
    _size = other._size;
    _capacity = other._capacity;
    _datas = nullptr;

    if (_capacity > 0)
    {
        const size_t alloc_size = item_size * _capacity;
        _datas = malloc(alloc_size);
        for (uint32_t i = 0; i < _size; ++i)
        {
            void* other_item = static_cast<char*>(other._datas) + i * item_size;
            void* item = static_cast<char*>(_datas) + i * item_size;
            ops->copy_construct(item, other_item);
        }
    }
}

void narray::move_init(narray&& other)
{
    _size = other._size;
    _capacity = other._capacity;
    _datas = other._datas;
    other._size = 0;
    other._capacity = 0;
    other._datas = nullptr;
}

void narray::destruct(size_t item_size, ntype::operations* ops)
{
    for (uint32_t i = 0; i < _size; ++i)
    {
        void* item = static_cast<char*>(_datas) + i * item_size;
        ops->destruct(item);
    }

    if (_datas)
        free(_datas);
}

void narray::reserve(uint32_t new_capacity, size_t item_size, ntype::operations* ops,
                     uint32_t* reserve_index)
{
    if (new_capacity > _capacity)
    {
        void* old_datas = _datas;
        uint32_t old_capacity = _capacity;
        _capacity = new_capacity;
        const size_t alloc_size = item_size * new_capacity;
        _datas = malloc(alloc_size);
        for (uint32_t old_i = 0, i = 0; old_i < _size; ++old_i, ++i)
        {
            if (reserve_index && old_i == *reserve_index)
                ++i;
            void* old_item = static_cast<char*>(old_datas) + old_i * item_size;
            void* item = static_cast<char*>(_datas) + i * item_size;
            ops->move_construct(item, old_item);
            ops->destruct(old_item);
        }
        free(old_datas);
    }
}

void narray::push_back(void* item_data, size_t item_size, ntype::operations* ops,
                       bool is_move)
{
    if (_size >= _capacity)
        reserve(narray_growth_capacity(_capacity), item_size, ops);
    void* push_item = static_cast<char*>(_datas) + _size * item_size;
    if (is_move)
        ops->move_construct(push_item, item_data);
    else
        ops->copy_construct(push_item, item_data);
    ++_size;
}

void narray::pop_back(size_t item_size, ntype::operations* ops)
{
    ops->destruct(static_cast<char*>(_datas) + (_size - 1) * item_size);
    --_size;
}

void narray::insert(void* item_data, size_t item_size, uint32_t index,
                    ntype::operations* ops, bool is_move)
{
    if (index >= _size)
        push_back(item_data, item_size, ops, is_move);
    else
    {
        if (_size >= _capacity)
        {
            reserve(narray_growth_capacity(_capacity), item_size, ops, &index);
        }
        else
        {
            for (int i = _size - 1; i >= static_cast<int>(index); --i)
            {
                char* item = static_cast<char*>(_datas) + i * item_size;
                ops->move_construct(item + item_size, item);
                ops->destruct(item);
            }
        }
        void* insert_item = static_cast<char*>(_datas) + index * item_size;
        if (is_move)
            ops->move_construct(insert_item, item_data);
        else
            ops->copy_construct(insert_item, item_data);
        ++_size;
    }
}

void narray::remove(size_t item_size, uint32_t index, ntype::operations* ops)
{
    if (index < _size)
    {
        for (uint32_t i = index; i < _size - 1; ++i)
        {
            char* item = static_cast<char*>(_datas) + i * item_size;
            ops->destruct(item);
            ops->move_construct(item, item + item_size);
        }
        ops->destruct(static_cast<char*>(_datas) + (_size - 1) * item_size);
        --_size;
    }
}

void narray::clear(size_t item_size, ntype::operations* ops)
{
    for (uint32_t i = 0; i < _size; ++i)
    {
        void* item = static_cast<char*>(_datas) + i * item_size;
        ops->destruct(item);
    }
    _size = 0;
}

} // namespace ntr