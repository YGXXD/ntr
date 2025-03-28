#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nfunction : nfield
{
    nfunction(ntype* owner_type, efield field_kind, const std::string& name)
        : nfield(owner_type, field_kind, name)
    {
    }
    nfunction(ntype* owner_type, efield field_kind, std::string&& name)
        : nfield(owner_type, field_kind, std::move(name))
    {
    }

    ntype* _return_type;
    std::vector<ntype*> _argument_types;
    std::function<void*(void*)> _function;
};

} // namespace ntr
