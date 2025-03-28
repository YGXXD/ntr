#pragma once

#include "ntype.h"
#include "neitem.h"
#include <list>
#include <unordered_map>
#include <iostream>

namespace ntr
{

struct nenum : ntype
{
    nenum(std::string_view name) : ntype(etype::eenum, name) {}

    template <etype E, typename T>
    friend struct nfactory;

    // template <typename T>
    // inline T get_value(std::string_view name) const
    // {
    //     return static_cast<T>(_str_map.at(name).second);
    // }

    // template <typename T>
    // inline std::string_view get_name(T value) const
    // {
    //     return _enum_map.at(static_cast<long>(value)).first;
    // }

    virtual std::vector<const nfield*> fields() const
    {
        std::vector<const nfield*> fields;
        for (const auto& item : _items)
        {
            fields.push_back(&item);
        }
        return fields;
    }

private:
    template <typename T>
    inline void add_eitem(std::string_view name, T value)
    {
        if (_str_map.find(name) == _str_map.end())
        {
            _items.emplace_back(this, name, static_cast<long>(value));
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