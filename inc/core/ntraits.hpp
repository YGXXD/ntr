#pragma once

#include "../type/ntype.hpp"
#include "../type/nnumeric.hpp"

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

template <typename T>
struct ntype_ops_traits
{
private:
    ntype_ops_traits();

public:
    NTR_SINGLETON_IMPL(ntype_ops_traits<T>)
    ntype::operations ops;
};

} // namespace ntr