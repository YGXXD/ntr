//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "field/nfunction.hpp"
#include "type/nclass.hpp"

namespace ntr
{

nfunction::nfunction(const ntype* parent_type, std::string_view name, bool is_static)
    : nfield(parent_type, efield::eproperty, name), _is_static(is_static)
{
    if (parent_type->kind() != ntype::etype::eclass)
        throw std::invalid_argument(
            "nfunction::nfunction : parent type is not class type");
}

nfunction::~nfunction() = default;

nobject nfunction::call(const std::vector<nwrapper>& arg_arr) const
{
    if (arg_arr.size() != _argument_types.size())
        throw std::invalid_argument("nfunction::call : argument size is wrong, need " +
                                    std::to_string(_argument_types.size()) +
                                    " arguments, but got " +
                                    std::to_string(arg_arr.size()));
    return _function(arg_arr);
}

const nclass* nfunction::class_type() const
{
    return static_cast<const nclass*>(parent_type());
}

} // namespace ntr
