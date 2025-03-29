#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nproperty : nfield
{
    nproperty(ntype* parent_type, efield kind, std::string_view name)
        : nfield(parent_type, kind, name)
    {
    }

    ntype* _property_type;
    std::function<void*(void*)> _getter;
    std::function<void(void*, void*)> _setter;
};

} // namespace ntr