#pragma once

#include "ntype.h"

namespace ntr
{

// static
template <typename T>
inline constexpr ntype::etype ntype::to_etype()
{
    if constexpr (std::is_same_v<T, int8_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, int16_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, int32_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, int64_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, uint8_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, uint16_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, uint32_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, uint64_t>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, float>)
        return etype::enumeric;
    else if constexpr (std::is_same_v<T, double>)
        return etype::enumeric;
    else if constexpr (std::is_enum_v<T>)
        return etype::eenum;
    else if constexpr (std::is_class_v<T>)
        return etype::eclass;
    else
        return etype::eunknown;
}

// construct
inline ntype::ntype(etype kind, std::string_view name) : _kind(kind), _name(name)
{
}

// get
inline ntype::etype ntype::kind() const
{
    return _kind;
}

inline std::string_view ntype::name() const
{
    return _name;
}

} // namespace ntr