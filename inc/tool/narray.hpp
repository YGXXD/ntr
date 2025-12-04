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

class NTR_API narray
{
public:
    NTR_INLINE uint32_t size() const { return _size; };
    NTR_INLINE bool empty() const { return _size == 0; };

protected:
    using item_equal_function = bool (*)(void*, void*);

    narray();
    void copy_init(const narray& other, size_t item_size, ntype::operations* ops);
    void move_init(narray&& other);
    void destruct(size_t item_size, ntype::operations* ops);

    void reserve(uint32_t new_capacity, size_t item_size, ntype::operations* ops,
                 uint32_t* reserve_index = nullptr);
    void push_back(void* item_data, size_t item_size, ntype::operations* ops,
                   bool is_move);
    void pop_back(size_t item_size, ntype::operations* ops);

    void insert(void* item_data, size_t item_size, uint32_t index, ntype::operations* ops,
                bool is_move);
    void remove(size_t item_size, uint32_t index, ntype::operations* ops);
    void clear(size_t item_size, ntype::operations* ops);
    NTR_INLINE void* begin() const { return _datas; };
    NTR_INLINE void* end(size_t item_size) const
    {
        return static_cast<char*>(_datas) + _size * item_size;
    };

    uint32_t _size;
    uint32_t _capacity;
    void* _datas;
};

} // namespace ntr