#include "../../inc/field/nproperty.hpp"
#include "../../inc/type/nclass.hpp"

namespace ntr
{

nproperty::nproperty(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
    if (parent_type->kind() != ntype::etype::eclass)
        throw std::invalid_argument("nproperty must be created from a class type");
}

nobject nproperty::get(const nreference& instance) const
{
    return _getter(instance);
}

void nproperty::set(const nreference& instance, const nreference& value) const
{
    _setter(instance, value);
}

const nclass* nproperty::class_type() const
{
    return static_cast<const nclass*>(parent_type());
}

} // namespace ntr
