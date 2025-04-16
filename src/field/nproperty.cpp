#include "../../inc/field/nproperty.h"

namespace ntr
{

nproperty::nproperty(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
}

nobject nproperty::get(const nreference& instance) const
{
    return _getter(instance);
}

void nproperty::set(const nreference& instance, const nreference& value) const
{
    _setter(instance, value);
}

} // namespace ntr
