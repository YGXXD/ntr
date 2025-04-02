#pragma once

#include "ntype.h"
#include <memory>
#include <list>
#include <unordered_map>

namespace ntr
{

struct nenum : ntype
{
    template <etype E, typename T>
    friend struct nfactory;

    nenum(std::string_view name);

    template <typename T>
    const struct neitem* get_eitem(T value) const;
    const struct neitem* get_eitem(std::string_view name) const;

private:
    void add_eitem(std::unique_ptr<neitem>&& item);
    void remove_eitem(std::string_view name);

    std::list<std::unique_ptr<neitem>> _items;
    std::unordered_map<std::string_view,
                       std::list<std::unique_ptr<neitem>>::const_iterator>
        _str_field_map;
    std::unordered_map<long, std::list<std::unique_ptr<neitem>>::const_iterator>
        _enum_field_map;
};

} // namespace ntr