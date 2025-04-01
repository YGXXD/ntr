#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nproperty : nfield
{
    template <typename T, typename ClassT>
    nproperty(ntype* parent_type, std::string_view name, T(ClassT::*member));
    template <typename T, typename ClassT>
    nproperty(ntype* parent_type, std::string_view name, T (ClassT::*getter)() const,
              void (ClassT::*setter)(const T&));

    const ntype* property_type() const;

private:
    nproperty(ntype* parent_type, std::string_view name);

    const ntype* _property_type;
    // std::function<nobject(nobject)> _getter;
    // std::function<void(nobject, nobject)> _setter;
};

} // namespace ntr