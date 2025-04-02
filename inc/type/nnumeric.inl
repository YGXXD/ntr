#pragma once

#include "nnumeric.h"

namespace ntr
{

// static
template <typename T>
inline constexpr nnumeric::enumeric nnumeric::to_enumeric()
{
    if constexpr (std::is_same_v<T, int8_t>)
        return enumeric::eint8;
    else if constexpr (std::is_same_v<T, int16_t>)
        return enumeric::eint16;
    else if constexpr (std::is_same_v<T, int32_t>)
        return enumeric::eint32;
    else if constexpr (std::is_same_v<T, int64_t>)
        return enumeric::eint64;
    else if constexpr (std::is_same_v<T, uint8_t>)
        return enumeric::euint8;
    else if constexpr (std::is_same_v<T, uint16_t>)
        return enumeric::euint16;
    else if constexpr (std::is_same_v<T, uint32_t>)
        return enumeric::euint32;
    else if constexpr (std::is_same_v<T, uint64_t>)
        return enumeric::euint64;
    else if constexpr (std::is_same_v<T, float>)
        return enumeric::efloat;
    else if constexpr (std::is_same_v<T, double>)
        return enumeric::edouble;
    else
        static_assert(!std::is_same_v<T, T>, "unknown type, to_enumeric template param "
                                             "\"T\" is unknown numeric type");
}

// construct
inline nnumeric::nnumeric(enumeric numeric_kind, std::string_view name)
    : ntype(etype::enumeric, name), _numeric_kind(numeric_kind)
{
    switch (numeric_kind)
    {
    case enumeric::eint8:
    case enumeric::eint16:
    case enumeric::eint32:
    case enumeric::eint64:
        _is_signed = true;
        _is_integral = true;
        break;
    case enumeric::euint8:
    case enumeric::euint16:
    case enumeric::euint32:
    case enumeric::euint64:
        _is_signed = false;
        _is_integral = true;
        break;
    case enumeric::efloat:
    case enumeric::edouble:
        _is_signed = false;
        _is_integral = false;
        break;
    }
}

// get
inline nnumeric::enumeric nnumeric::numeric_kind() const
{
    return _numeric_kind;
}

inline bool nnumeric::is_signed() const
{
    return _is_signed;
}

inline bool nnumeric::is_floating_point() const
{
    return !_is_integral;
}

inline bool nnumeric::is_integral() const
{
    return _is_integral;
}

} // namespace ntr