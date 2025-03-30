#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nproperty : nfield
{
private:
    nproperty(ntype* parent_type, std::string_view name)
        : nfield(parent_type, efield::efunction, name)
    {
    }

    ntype* _property_type;
    // std::function<void*(void*)> _getter;
    // std::function<void(void*, void*)> _setter;
};

} // namespace ntr