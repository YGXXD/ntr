//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"
#include "../field/neitem.hpp"

namespace ntr
{

class NTR_API nenum : public ntype
{
public:
    using enum_integer_type = long;

    static enum_integer_type get_value(const class nobject& enum_);
    static void set_value(nobject& enum_, enum_integer_type value);

    nenum(std::string_view name, uint32_t size, uint32_t align, operations* ops);
    nenum(const nenum&) = delete;
    nenum(nenum&&) = delete;
    nenum& operator=(const nenum&) = delete;
    nenum& operator=(nenum&&) = delete;

    void add_eitem(std::unique_ptr<neitem>&& item);
    void remove_eitem(std::string_view name);

    NTR_INLINE auto eitem_begin() const { return _items.begin(); }
    NTR_INLINE auto eitem_end() const { return _items.end(); }
    const neitem* get_eitem(enum_integer_type value) const;
    const neitem* get_eitem(std::string_view name) const;
    bool has_eitem(std::string_view name) const;
    bool has_eitem(enum_integer_type value) const;

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