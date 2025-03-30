#pragma once

#include "nbasic.h"

namespace ntr
{

// static
template <typename T>
inline constexpr nbasic::ebasic nbasic::to_ebasic()
{
    if constexpr (std::is_same_v<T, bool>)
        return ebasic::ebool;
    else if constexpr (std::is_same_v<T, char>)
        return ebasic::echar;
    else if constexpr (std::is_same_v<T, wchar_t>)
        return ebasic::ewchar;
    else if constexpr (std::is_same_v<T, int8_t>)
        return ebasic::eint8;
    else if constexpr (std::is_same_v<T, int16_t>)
        return ebasic::eint16;
    else if constexpr (std::is_same_v<T, int32_t>)
        return ebasic::eint32;
    else if constexpr (std::is_same_v<T, int64_t>)
        return ebasic::eint64;
    else if constexpr (std::is_same_v<T, uint8_t>)
        return ebasic::euint8;
    else if constexpr (std::is_same_v<T, uint16_t>)
        return ebasic::euint16;
    else if constexpr (std::is_same_v<T, uint32_t>)
        return ebasic::euint32;
    else if constexpr (std::is_same_v<T, uint64_t>)
        return ebasic::euint64;
    else if constexpr (std::is_same_v<T, float>)
        return ebasic::efloat;
    else if constexpr (std::is_same_v<T, double>)
        return ebasic::edouble;
    else if constexpr (std::is_same_v<T, long double>)
        return ebasic::elongdouble;
    else
        static_assert(!std::is_same_v<T, T>, "unknown type, to_ebasic template param "
                                             "\"T\" is unknown fundamental type");
}

// construct
inline nbasic::nbasic(ebasic basic_kind, std::string_view name)
    : ntype(etype::ebasic, name), _basic_kind(basic_kind)
{
}

// get
inline nbasic::ebasic nbasic::basic_kind() const
{
    return _basic_kind;
}

} // namespace ntr