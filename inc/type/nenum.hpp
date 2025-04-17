#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API nenum : public ntype
{
public:
    nenum(std::string_view name, uint32_t size);

    void add_eitem(std::unique_ptr<class neitem>&& item);
    void remove_eitem(std::string_view name);

    const neitem* get_eitem(long value) const;
    const neitem* get_eitem(std::string_view name) const;

    // long get_value(class nobject& obj) const;
    // void set_value(nobject& obj, long value) const;

private:
    std::list<std::unique_ptr<neitem>> _items;
    std::unordered_map<std::string_view,
                       std::list<std::unique_ptr<neitem>>::const_iterator>
        _str_field_map;
    std::unordered_map<long, std::list<std::unique_ptr<neitem>>::const_iterator>
        _enum_field_map;
};

} // namespace ntr