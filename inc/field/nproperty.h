#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nproperty : nfield
{
    template <typename P>
    nproperty(ntype* parent_type, std::string_view name, P menmber_object_ptr);
    template <typename GetF, typename SetF>
    nproperty(ntype* parent_type, std::string_view name, GetF getter, SetF setter);

    const ntype* property_type() const;

private:
    nproperty(ntype* parent_type, std::string_view name);

    ntype* _property_type;
    // std::function<void*(void*)> _getter;
    // std::function<void(void*, void*)> _setter;
};

} // namespace ntr