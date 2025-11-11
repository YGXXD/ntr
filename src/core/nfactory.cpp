//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "core/nfactory.hpp"

namespace ntr
{

// ntype::etype::eunknown void impl
nfactory<ntype::etype::eunknown, void>::nfactory()
    : _type(ntype::etype::eunknown, 0, 0, &ntype_ops_traits<void>::instance().ops, "")
{
}

} // namespace ntr
