#pragma once

#include "../type/ntype.h"
#include "../type/nnumeric.h"

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
NTR_INLINE constexpr ntype::etype make_etype()
{
    if constexpr (is_etype_numeric<T>())
        return ntype::etype::enumeric;
    else if constexpr (is_etype_enum<T>())
        return ntype::etype::eenum;
    else if constexpr (is_etype_class<T>())
        return ntype::etype::eclass;
    else
        return ntype::etype::eunknown;
}

template <typename T>
NTR_INLINE constexpr nnumeric::enumeric make_enumeric()
{
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
    else
        static_assert(!std::is_same_v<T, T>, "unknown type, to_enumeric template param "
                                             "\"T\" is unknown numeric type");
}

} // namespace ntr