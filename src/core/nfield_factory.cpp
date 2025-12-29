//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "core/nfield_factory.hpp"

namespace ntr
{

std::unique_ptr<neitem> nfield_factory::make_eitem(ntype* parent_type,
                                                   std::string_view name,
                                                   nenum::enum_integer_type value)
{
    return std::make_unique<neitem>(parent_type, name, value);
}

} // namespace ntr
