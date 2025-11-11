//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "field/nfield.hpp"

namespace ntr
{

nfield::nfield(const class ntype* parent_type, efield kind, std::string_view name)
    : _kind(kind), _name(name), _parent_type(parent_type)
{
}

nfield::~nfield() = default;

} // namespace ntr
