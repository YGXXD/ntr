#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nfunction : nfield
{
private:
    nfunction(ntype* parent_type, std::string_view name)
        : nfield(parent_type, efield::eproperty, name)
    {
    }

    ntype* _return_type;
    std::vector<ntype*> _argument_types;
    // std::vector<ntype*> _argument_types;
    // std::function<void*(void*)> _function;
};

} // namespace ntr
