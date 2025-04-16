#include "../../inc/field/nfunction.h"

namespace ntr
{

nfunction::nfunction(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
}

nobject nfunction::invoke(const std::vector<nreference>& args) const
{
    if (args.size() != _argument_types.size())
        throw std::invalid_argument("invoke function with wrong argument size");
    return _function(args);
}

} // namespace ntr
