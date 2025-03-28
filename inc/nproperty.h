#pragma once

#include "nfunction.h"

namespace ntr
{

struct nproperty : nfield
{
    nproperty(ntype* owner_type, efield field_kind, std::string_view name)
        : nfield(owner_type, field_kind, name)
    {
    }

    ntype* _property_type;
    nfunction* _getter;
    nfunction* _setter;
};

} // namespace ntr