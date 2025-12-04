//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"
#include "../tool/ntable.hpp"
#include "../tool/ntraits.hpp"

namespace ntr
{

class NTR_API nenum : public ntype
{
public:
    static enum_integer_type get_value(const class nobject& enum_);
    static void set_value(nobject& enum_, enum_integer_type value);

    nenum(uint32_t size, uint32_t align, operations* ops, std::string_view name);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(nenum)
    ~nenum();

    void add_eitem(std::unique_ptr<class neitem>&& item);
    void remove_eitem(std::string_view name);

    NTR_INLINE const auto& eitems() const { return _eitems; }
    const neitem* get_eitem(enum_integer_type value) const;
    const neitem* get_eitem(std::string_view name) const;
    bool has_eitem(std::string_view name) const;
    bool has_eitem(enum_integer_type value) const;

private:
    std::vector<std::unique_ptr<neitem>> _eitems;
    nhash_map<std::string_view, neitem*> _str_field_map;
    nhash_map<enum_integer_type, neitem*> _enum_field_map;
};

} // namespace ntr