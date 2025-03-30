#pragma once

#include "ntype.h"
#include "../field/nproperty.h"
#include "../field/nfunction.h"

namespace ntr
{

struct nclass : ntype
{
    nclass(std::string_view name);

    std::vector<nproperty> _properties;
    std::vector<nfunction> _functions;
};

} // namespace ntr