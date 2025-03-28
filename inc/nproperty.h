#pragma once

#include "nfunction.h"

namespace ntr
{

struct nproperty : nfield
{
    nproperty(ntype* parent_type, efield kind, std::string_view name)
        : nfield(parent_type, kind, name)
    {
    }

    ntype* _property_type;
    nfunction* _getter;
    nfunction* _setter;
};

} // namespace ntr