#pragma once

#include "../type/ntype.hpp"
#include "../type/nnumeric.hpp"
#include "../type/npointer.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE constexpr bool is_etype_numeric()
{
    return std::is_same_v<int8_t, T> || std::is_same_v<int16_t, T> ||
           std::is_same_v<int32_t, T> || std::is_same_v<int64_t, T> ||
           std::is_same_v<uint8_t, T> || std::is_same_v<uint16_t, T> ||
           std::is_same_v<uint32_t, T> || std::is_same_v<uint64_t, T> ||
           std::is_same_v<float, T> || std::is_same_v<double, T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_enum()
{
    return std::is_enum_v<T> && !std::is_const_v<T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_class()
{
    return std::is_class_v<T> && !std::is_const_v<T>;
}

template <typename T>
NTR_INLINE constexpr bool is_etype_pointer()
{
    return std::is_pointer_v<T> && !std::is_const_v<T>;
}

template <typename T>
NTR_INLINE constexpr ntype::etype make_etype()
{
    if constexpr (is_etype_numeric<T>())
        return ntype::etype::enumeric;
    else if constexpr (is_etype_enum<T>())
        return ntype::etype::eenum;
    else if constexpr (is_etype_class<T>())
        return ntype::etype::eclass;
    else if constexpr (is_etype_pointer<T>())
        return ntype::etype::epointer;
    else
        return ntype::etype::eunknown;
}

template <typename T>
struct ntype_ops_traits
{
private:
    ntype_ops_traits() : ops()
    {
        {
            if constexpr (std::is_default_constructible_v<T>)
            {
                ops.construct = [](void* self_data) -> void
                {
                    new (self_data) T();
                };
            }
            if constexpr (std::is_copy_constructible_v<T>)
            {
                ops.copy = [](void* self_data, const void* const other_data) -> void
                {
                    new (self_data) T(*static_cast<const T*>(other_data));
                };
            }
            if constexpr (std::is_move_constructible_v<T>)
            {
                ops.move = [](void* self_data, void* other_data) -> void
                {
                    new (self_data) T(std::move(*static_cast<T*>(other_data)));
                };
            }
            if constexpr (std::is_destructible_v<T>)
            {
                ops.destruct = [](void* self_data) -> void
                {
                    static_cast<T*>(self_data)->~T();
                };
            }
        }
    }

public:
    NTR_SINGLETON_IMPL(ntype_ops_traits<T>)
    ntype::operations ops;
};

template <typename T>
NTR_INLINE constexpr nnumeric::enumeric make_enumeric()
{
    static_assert(is_etype_numeric<T>(), "unknown type, to_enumeric template param "
                                         "\"T\" is unknown numeric type");
    if constexpr (std::is_same_v<T, int8_t>)
        return nnumeric::enumeric::eint8;
    else if constexpr (std::is_same_v<T, int16_t>)
        return nnumeric::enumeric::eint16;
    else if constexpr (std::is_same_v<T, int32_t>)
        return nnumeric::enumeric::eint32;
    else if constexpr (std::is_same_v<T, int64_t>)
        return nnumeric::enumeric::eint64;
    else if constexpr (std::is_same_v<T, uint8_t>)
        return nnumeric::enumeric::euint8;
    else if constexpr (std::is_same_v<T, uint16_t>)
        return nnumeric::enumeric::euint16;
    else if constexpr (std::is_same_v<T, uint32_t>)
        return nnumeric::enumeric::euint32;
    else if constexpr (std::is_same_v<T, uint64_t>)
        return nnumeric::enumeric::euint64;
    else if constexpr (std::is_same_v<T, float>)
        return nnumeric::enumeric::efloat;
    else if constexpr (std::is_same_v<T, double>)
        return nnumeric::enumeric::edouble;
}

template <nnumeric::enumeric numeric_kind>
NTR_INLINE constexpr auto make_numeric_type()
{
    if constexpr (numeric_kind == nnumeric::enumeric::eint8)
        return int8_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::eint16)
        return int16_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::eint32)
        return int32_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::eint64)
        return int64_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::euint8)
        return uint8_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::euint16)
        return uint16_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::euint32)
        return uint32_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::euint64)
        return uint64_t();
    else if constexpr (numeric_kind == nnumeric::enumeric::efloat)
        return float();
    else if constexpr (numeric_kind == nnumeric::enumeric::edouble)
        return double();
}

template <typename T>
NTR_INLINE constexpr uint8_t make_pointer_depth()
{
    if constexpr (std::is_pointer_v<T>)
        return 1 + make_pointer_depth<std::remove_pointer_t<T>>();
    else
        return 0;
}

} // namespace ntr