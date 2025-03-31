#pragma once

#include "nclass.h"

namespace ntr
{

// construct
inline nclass::nclass(std::string_view name) : ntype(etype::eclass, name)
{
}

// logic
template <typename F>
inline void nclass::add_function(std::string_view name, F fun)
{
    _functions.emplace_back(this, name, fun);
}

template <typename M>
inline void nclass::add_property(std::string_view name, M member)
{
    _properties.emplace_back(this, name, member);
}

template <typename Get, typename Set>
inline void nclass::add_property(std::string_view name, Get getter, Set setter)
{
    _properties.emplace_back(this, name, getter, setter);
}

inline void nclass::remove(std::string_view name)
{
    _functions.erase(std::find_if(_functions.begin(), _functions.end(),
                                  [name](const nfunction& function)
    { return function.name() == name; }));
    _properties.erase(std::find_if(_properties.begin(), _properties.end(),
                                   [name](const nproperty& property)
    { return property.name() == name; }));
}

inline const nfunction& nclass::get_function(std::string_view name) const
{
    return *std::find_if(_functions.begin(), _functions.end(),
                         [name](const nfunction& function)
    { return function.name() == name; });
}

inline const nproperty& nclass::get_property(std::string_view name) const
{
    return *std::find_if(_properties.begin(), _properties.end(),
                         [name](const nproperty& property)
    { return property.name() == name; });
}

} // namespace ntr