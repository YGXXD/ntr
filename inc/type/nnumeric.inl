#pragma once

#include "nnumeric.h"

namespace ntr
{

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

} // namespace ntr