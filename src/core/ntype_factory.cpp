//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "core/ntype_factory.hpp"

namespace ntr
{

// ntype::etype::eunknown void impl
ntype_factory<ntype::etype::eunknown, void>::ntype_factory()
    : _type(ntype::etype::eunknown, 0, 0, nullptr, "")
{
}

} // namespace ntr
