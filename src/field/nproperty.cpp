//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "field/nproperty.hpp"
#include "type/nclass.hpp"

namespace ntr
{

nproperty::nproperty(const ntype* parent_type, std::string_view name,
                     const ntype* property_type,
                     std::function<nobject(const nwrapper&)>&& getter,
                     std::function<void(const nwrapper&, const nwrapper&)>&& setter)
    : nfield(parent_type, efield::eproperty, name), _property_type(property_type),
      _getter(std::move(getter)), _setter(std::move(setter))
{
    if (parent_type->kind() != ntype::etype::eclass)
        throw std::invalid_argument(
            "nproperty::nproperty : parent type is not class type");
}

nproperty::~nproperty() = default;

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
