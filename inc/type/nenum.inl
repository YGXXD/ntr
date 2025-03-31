#pragma once

#include "nenum.h"

namespace ntr
{

// construct
inline nenum::nenum(std::string_view name) : ntype(etype::eenum, name)
{
}

// logic
template <typename T>
inline void nenum::add_eitem(std::string_view name, T value)
{
    if (_str_map.find(name) == _str_map.end())
    {
        _items.emplace_back(this, name, value);
        std::list<neitem>::const_iterator item = --_items.end();
        _str_map.insert({ item->name(), item });
        _enum_map.insert({ item->value(), item });
    }
}

inline void nenum::remove_eitem(std::string_view name)
{
    if (_str_map.find(name) != _str_map.end())
    {
        auto item = _str_map.at(name);
        _items.erase(item);
        _str_map.erase(item->name());
        _enum_map.erase(item->value());
    }
}

template <typename T>
inline const neitem& nenum::get_eitem(T value) const
{
    return *_enum_map.at(static_cast<long>(value));
}

inline const neitem& nenum::get_eitem(std::string_view name) const
{
    return *_str_map.at(std::string_view(name));
}

} // namespace ntr