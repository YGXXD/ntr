#pragma once

#include "../type/ntype.h"
#include "../type/nnumeric.h"

namespace ntr
{

template <typename T>
NTR_INLINE constexpr bool is_etype_numeric();

template <typename T>
NTR_INLINE constexpr bool is_etype_enum();

template <typename T>
NTR_INLINE constexpr bool is_etype_class();

template <typename T>
NTR_INLINE constexpr ntype::etype make_etype();

template <typename T>
NTR_INLINE constexpr nnumeric::enumeric make_enumeric();

} // namespace ntr