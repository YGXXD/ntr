//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "core/nregistrar.hpp"
#include "type/ntype.hpp"

namespace ntr
{

const ntype* nregistrar::get_type(std::string_view name) const
{
    auto it = _type_map.find(name);
    if (it == _type_map.end())
        throw std::logic_error((std::string("nregistrar::get_type : type \"") +
                                std::string(name) + std::string("\" not registered"))
                                   .c_str());
    return it->second;
}

void nregistrar::regist_type(std::string_view name, ntype* type)
{
    if (_type_map.find(name) != _type_map.end())
        throw std::logic_error((std::string("nregistrar::regist_type : type \"") +
                                std::string(name) + std::string("\" already registered"))
                                   .c_str());
    type->regist(name);
    _type_map.insert({ type->name(), type });
}

} // namespace ntr