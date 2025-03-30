#pragma once

#include "ntype.h"

namespace ntr
{

// static
template <typename T>
inline constexpr ntype::etype ntype::to_etype()
{
    if constexpr (std::is_fundamental_v<T>)
        return etype::ebasic;
    else if constexpr (std::is_enum_v<T>)
        return etype::eenum;
    else if constexpr (std::is_class_v<T>)
        return etype::eclass;
    else
        static_assert(!std::is_same_v<T, T>,
                      "unknown type, to_etype template param \"T\" must be "
                      "fundamental, enum and class");
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