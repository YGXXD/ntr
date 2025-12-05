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
    NTR_INLINE void* begin() const { return _datas; }
    NTR_INLINE void* end(size_t item_size) const
    {
        return static_cast<char*>(_datas) + _size * item_size;
    }

    uint32_t _size;
    uint32_t _capacity;
    void* _datas;
};

template <class T>
struct array_iterator
{
    array_iterator(void* _item);
    NTR_INLINE array_iterator& operator++();
    NTR_INLINE array_iterator operator++(int);
    NTR_INLINE bool operator==(const array_iterator& other) const;
    NTR_INLINE bool operator!=(const array_iterator& other) const;
    NTR_INLINE T& operator*();
    NTR_INLINE const T& operator*() const;
    NTR_INLINE T* operator->();
    NTR_INLINE const T* operator->() const;

private:
    void* _item;
};

template <class Value>
class nvector : public narray
{
public:
    using item_type = Value;
    using iterator = array_iterator<item_type>;
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
    NTR_INLINE void insert(const item_type& item, uint32_t index);
    NTR_INLINE void insert(item_type&& item, uint32_t index);
    NTR_INLINE void remove(uint32_t index);
    NTR_INLINE void remove(const iterator& it);
    NTR_INLINE void clear();
    NTR_INLINE iterator begin() const;
    NTR_INLINE iterator end() const;
    NTR_INLINE Value& at(uint32_t index);
    NTR_INLINE const Value& at(uint32_t index) const;
    NTR_INLINE Value& operator[](uint32_t index);
    NTR_INLINE const Value& operator[](uint32_t index) const;
};

} // namespace ntr

#include "../impl/tool/narray.inl"