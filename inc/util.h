#pragma once

#include "nbasic.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

template <typename T>
struct singleton
{
    static inline T& instance()
    {
        static T _instance;
        return _instance;
    }
};

template <typename T>
static inline constexpr etype cast_etype()
{
    if constexpr (std::is_fundamental_v<T>)
        return etype::ebasic;
    else if constexpr (std::is_enum_v<T>)
        return etype::eenum;
    else if constexpr (std::is_class_v<T>)
        return etype::eclass;
    else
        static_assert(false, "unknown type");
}

template <typename T>
static inline constexpr ebasic cast_ebasic()
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
        static_assert(false, "unknown type");
}

} // namespace ntr