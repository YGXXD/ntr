#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nfunction : nfield
{
    nfunction(ntype* parent_type, efield kind, std::string_view name)
        : nfield(parent_type, kind, name)
    {
    }

    ntype* _return_type;
    std::vector<ntype*> _argument_types;
    std::function<void*(void*)> _function;
};

} // namespace ntr
