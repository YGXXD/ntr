#pragma once

#include "ntype.h"
#include <list>
#include <unordered_map>

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

private:
    using EnumItem = std::pair<std::string, long>;

    template <typename T>
    inline void add_item(std::string_view name, T value)
    {
        if (_str_map.find(name) == _str_map.end())
        {
            _items.emplace_back(name, static_cast<long>(value));
            const auto& item = _items.back();
            _str_map.insert({ item.first, item });
            _enum_map.insert({ item.second, item });
        }
    }

    inline void remove_item(std::string_view name)
    {
        if (_str_map.find(name) != _str_map.end())
        {
            const auto& item = _str_map.at(name);
            _items.erase(std::find(_items.begin(), _items.end(), item));
            _str_map.erase(item.first);
            _enum_map.erase(item.second);
        }
    }

    std::list<EnumItem> _items;
    std::unordered_map<std::string_view, const EnumItem&> _str_map;
    std::unordered_map<long, const EnumItem&> _enum_map;
};

} // namespace ntr