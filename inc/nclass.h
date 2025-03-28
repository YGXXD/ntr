#pragma once

#include "ntype.h"

namespace ntr
{

struct nclass : ntype
{
    nclass(std::string_view name) : ntype(etype::eclass, name) {}
};

} // namespace ntr