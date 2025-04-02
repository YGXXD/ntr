#pragma once

#include "nenum.h"
#include "../field/neitem.h"

namespace ntr
{

// construct
inline nenum::nenum(std::string_view name) : ntype(etype::eenum, name)
{
}

inline void nenum::add_eitem(std::unique_ptr<neitem>&& item)
{
    if (_str_field_map.find(item.get()->name()) == _str_field_map.end())
    {
        _items.push_back(std::move(item));
        auto item = --_items.end();
        _str_field_map.insert({ item->get()->name(), item });
        _enum_field_map.insert({ item->get()->value(), item });
    }
}

inline void nenum::remove_eitem(std::string_view name)
{
    if (_str_field_map.find(name) != _str_field_map.end())
    {
        auto item = _str_field_map.at(name);
        _str_field_map.erase(item->get()->name());
        _enum_field_map.erase(item->get()->value());
        _items.erase(item);
    }
}

template <typename T>
inline const neitem* nenum::get_eitem(T value) const
{
    return _enum_field_map.at(static_cast<long>(value))->get();
}

inline const neitem* nenum::get_eitem(std::string_view name) const
{
    return _str_field_map.at(std::string_view(name))->get();
}

} // namespace ntr