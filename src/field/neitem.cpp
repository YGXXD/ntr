//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "field/neitem.hpp"
#include "type/nenum.hpp"
namespace ntr
{

neitem::neitem(ntype* parent_type, std::string_view name, enum_integer_type value)
    : nfield(parent_type, efield::eeitem, name), _value(value)
{
    if (parent_type->kind() != ntype::etype::eenum)
        throw std::invalid_argument("neitem::neitem : parent type is not enum type");
}

neitem::~neitem() = default;

const nenum* neitem::enum_type() const
{
    return static_cast<const nenum*>(parent_type());
}

} // namespace ntr
