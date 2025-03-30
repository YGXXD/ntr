#pragma once

#include "ntype.h"
#include "../field/neitem.h"
#include <list>
#include <unordered_map>

namespace ntr
{

struct nenum : ntype
{
    nenum(std::string_view name) : ntype(etype::eenum, name) {}

    template <etype E, typename T>
    friend struct nfactory;

    template <typename T>
    inline std::enable_if_t<std::is_enum_v<T>, const neitem&> get_eitem(T value) const
    {
        return *_enum_map.at(static_cast<long>(value));
    }

    inline const neitem& get_eitem(std::string_view name) const
    {
        return *_str_map.at(static_cast<std::string_view>(name));
    }

private:
    template <typename T>
    inline void add_eitem(std::string_view name, T value)
    {
        if (_str_map.find(name) == _str_map.end())
        {
            _items.emplace_back(this, name, value);
            std::list<neitem>::const_iterator item = --_items.end();
            _str_map.insert({ item->name(), item });
            _enum_map.insert({ item->value(), item });
        }
    }

    inline void remove_eitem(std::string_view name)
    {
        if (_str_map.find(name) != _str_map.end())
        {
            auto item = _str_map.at(name);
            _items.erase(item);
            _str_map.erase(item->name());
            _enum_map.erase(item->value());
        }
    }

    std::list<neitem> _items;
    std::unordered_map<std::string_view, std::list<neitem>::const_iterator> _str_map;
    std::unordered_map<long, std::list<neitem>::const_iterator> _enum_map;
};

} // namespace ntr