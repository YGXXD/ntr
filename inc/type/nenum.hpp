#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API nenum : public ntype
{
public:
    using enum_integer_type = long;
    
    static enum_integer_type get_value(class nobject& obj);
    static void set_value(nobject& obj, enum_integer_type value);

    nenum(std::string_view name, uint32_t size, operations* ops);

    void add_eitem(std::unique_ptr<class neitem>&& item);
    void remove_eitem(std::string_view name);

    const neitem* get_eitem(enum_integer_type value) const;
    const neitem* get_eitem(std::string_view name) const;

private:
    std::list<std::unique_ptr<neitem>> _items;
    std::unordered_map<std::string_view,
                       std::list<std::unique_ptr<neitem>>::const_iterator>
        _str_field_map;
    std::unordered_map<enum_integer_type,
                       std::list<std::unique_ptr<neitem>>::const_iterator>
        _enum_field_map;
};

} // namespace ntr