#pragma once

#include "ntype.h"
#include <memory>
#include <list>
#include <unordered_map>

namespace ntr
{

struct nenum : ntype
{
    nenum(std::string_view name);

    void add_eitem(std::unique_ptr<struct neitem>&& item);
    void remove_eitem(std::string_view name);

    template <typename T>
    const neitem* get_eitem(std::enable_if_t<!std::is_same_v<T, long>, T> value) const;
    const neitem* get_eitem(long value) const;
    const neitem* get_eitem(std::string_view name) const;

private:
    std::list<std::unique_ptr<neitem>> _items;
    std::unordered_map<std::string_view,
                       std::list<std::unique_ptr<neitem>>::const_iterator>
        _str_field_map;
    std::unordered_map<long, std::list<std::unique_ptr<neitem>>::const_iterator>
        _enum_field_map;
};

} // namespace ntr