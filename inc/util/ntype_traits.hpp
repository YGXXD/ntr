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
NTR_INLINE constexpr bool is_etype_container();

template <typename T>
NTR_INLINE constexpr ntype::etype make_etype();

template <typename T>
NTR_INLINE constexpr nnumeric::enumeric make_enumeric();

template <typename T>
NTR_INLINE constexpr bool is_econtainer_map();

} // namespace ntr

#include "../impl/util/ntype_traits.inl"