#pragma once

#include "nfunction.h"

namespace ntr
{

struct nproperty : nfield
{
    nproperty(ntype* owner_type, efield field_kind, const std::string& name)
        : nfield(owner_type, field_kind, name)
    {
    }
    nproperty(ntype* owner_type, efield field_kind, std::string&& name)
        : nfield(owner_type, field_kind, std::move(name))
    {
    }

    ntype* _property_type;
    nfunction* _getter;
    nfunction* _setter;
};

} // namespace ntr