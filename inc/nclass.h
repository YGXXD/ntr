#pragma once

#include "ntype.h"
#include "nproperty.h"
#include "nfunction.h"

namespace ntr
{

struct nclass : ntype
{
    nclass(std::string_view name) : ntype(etype::eclass, name) {}

    std::vector<nproperty> _properties;
    std::vector<nfunction> _functions;
};

} // namespace ntr