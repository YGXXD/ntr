#pragma once

#include "ntype.h"

namespace ntr
{

// static
template <typename T>
inline constexpr bool ntype::is_numeric()
{
    return std::is_same_v<int8_t, T> || std::is_same_v<int16_t, T> ||
           std::is_same_v<int32_t, T> || std::is_same_v<int64_t, T> ||
           std::is_same_v<uint8_t, T> || std::is_same_v<uint16_t, T> ||
           std::is_same_v<uint32_t, T> || std::is_same_v<uint64_t, T> ||
           std::is_same_v<float, T> || std::is_same_v<double, T>;
}

template <typename T>
inline constexpr bool ntype::is_enum()
{
    return std::is_enum_v<T> && !std::is_const_v<T>;
}

template <typename T>
inline constexpr bool ntype::is_class()
{
    return std::is_class_v<T> && !std::is_const_v<T>;
}

template <typename T>
inline constexpr ntype::etype ntype::to_etype()
{
    if constexpr (is_numeric<T>())
        return etype::enumeric;
    else if constexpr (is_enum<T>())
        return etype::eenum;
    else if constexpr (is_class<T>())
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