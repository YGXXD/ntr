#include "../../inc/field/nproperty.hpp"
#include "../../inc/implement.hpp"

namespace ntr
{

nproperty::nproperty(const ntype* parent_type, std::string_view name,
                     const ntype* property_type)
    : nfield(parent_type, efield::eproperty, name), _property_type(property_type)
{
    if (parent_type->kind() != ntype::etype::eclass)
        throw std::invalid_argument(
            "nproperty::nproperty : parent type is not class type");
}

nobject nproperty::get(const nwrapper& instance) const
{
    return _getter(instance);
}

void nproperty::set(const nwrapper& instance, const nwrapper& value) const
{
    _setter(instance, value);
}

const nclass* nproperty::class_type() const
{
    return static_cast<const nclass*>(parent_type());
}

} // namespace ntr
