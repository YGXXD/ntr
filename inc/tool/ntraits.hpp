//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../type/ntype.hpp"
#include "../type/nnumeric.hpp"

namespace ntr
{

using enum_integer_type = long;

template <typename T>
NTR_INLINE constexpr bool is_etype_type();

template <typename T>
NTR_INLINE constexpr bool is_etype_numeric();

template <typename T>
NTR_INLINE constexpr bool is_etype_enum();

template <typename T>
NTR_INLINE constexpr bool is_etype_class();

template <typename T>
NTR_INLINE constexpr bool is_etype_pointer();

template <typename T>
NTR_INLINE constexpr ntype::etype make_etype();

template <typename T>
NTR_INLINE constexpr nnumeric::enumeric make_enumeric();

template <typename T>
NTR_INLINE constexpr uint8_t make_pointer_depth();

template <typename T>
struct ntype_ops_traits
{
private:
    ntype_ops_traits();
    ~ntype_ops_traits() = default;

public:
    NTR_SINGLETON_IMPL(ntype_ops_traits<T>)
    ntype::operations ops;
};

} // namespace ntr

#include "../impl/tool/ntraits.inl"