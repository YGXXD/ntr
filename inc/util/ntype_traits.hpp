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
NTR_INLINE constexpr bool is_etype_std_pair();

template <typename T>
NTR_INLINE constexpr bool is_etype_container();

template <typename T>
using make_type_t = std::enable_if_t<
    !std::is_array_v<std::remove_cv_t<std::remove_reference_t<T>>>,
    std::conditional_t<std::is_pointer_v<T>,
                       std::add_pointer_t<std::remove_cv_t<
                           std::remove_reference_t<std::remove_pointer_t<T>>>>,
                       std::remove_cv_t<std::remove_reference_t<T>>>>;

template <typename T>
NTR_INLINE constexpr ntype::etype make_etype();

template <nnumeric::enumeric numeric_kind>
using make_numeric_type_t =
    std::tuple_element_t<static_cast<size_t>(numeric_kind), nnumeric::numeric_types>;

template <typename T>
NTR_INLINE constexpr nnumeric::enumeric make_enumeric();

} // namespace ntr

#include "../impl/util/ntype_traits.inl"