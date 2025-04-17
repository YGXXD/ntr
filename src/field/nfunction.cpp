#include "../../inc/field/nfunction.h"
#include "../../inc/type/nclass.h"

namespace ntr
{

nfunction::nfunction(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
    if (parent_type->kind() != ntype::etype::eclass)
        throw std::invalid_argument("nfunction must be created from a class type");
}

nobject nfunction::invoke(const std::vector<nreference>& args) const
{
    if (args.size() != _argument_types.size())
        throw std::invalid_argument("invoke function with wrong argument size");
    return _function(args);
}

const nclass* nfunction::class_type() const
{
    return static_cast<const nclass*>(parent_type());
}

} // namespace ntr
