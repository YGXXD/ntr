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
    : _kind(kind), _name_size(name.size()), _name(new char[_name_size + 1]),
      _parent_type(parent_type)
{
    std::memcpy(_name, name.data(), _name_size);
    _name[_name_size] = '\0';
}

nfield::~nfield()
{
    delete[] _name;
};

} // namespace ntr
