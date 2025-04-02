#pragma once

#include "nfield.h"

namespace ntr
{

class nproperty : public nfield
{
public:
    nproperty(ntype* parent_type, std::string_view name);
    template <typename T, typename ClassT>
    nproperty(ntype* parent_type, std::string_view name, T(ClassT::*member));
    template <typename T, typename ClassT>
    nproperty(ntype* parent_type, std::string_view name, T (ClassT::*getter)() const,
              void (ClassT::*setter)(const T&));

    inline const ntype* property_type() const { return _property_type; }

private:
    const ntype* _property_type;
    // std::function<nobject(nobject)> _getter;
    // std::function<void(nobject, nobject)> _setter;
};

} // namespace ntr