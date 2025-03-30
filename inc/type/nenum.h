#pragma once

#include "ntype.h"
#include "../field/neitem.h"
#include <list>
#include <unordered_map>

namespace ntr
{

struct nenum : ntype
{
    nenum(std::string_view name);

    template <etype E, typename T>
    friend struct nfactory;

    template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
    const neitem& get_eitem(T value) const;
    const neitem& get_eitem(std::string_view name) const;

private:
    template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
    void add_eitem(std::string_view name, T value);
    void remove_eitem(std::string_view name);

    std::list<neitem> _items;
    std::unordered_map<std::string_view, std::list<neitem>::const_iterator> _str_map;
    std::unordered_map<long, std::list<neitem>::const_iterator> _enum_map;
};

} // namespace ntr