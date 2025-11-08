//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "nfield.hpp"
#include "../core/nobject.hpp"

namespace ntr
{

class NTR_API nproperty : public nfield
{
public:
    nproperty(const ntype* parent_type, std::string_view name, const ntype* property_type);
    template <typename T, typename ClassT>
    nproperty(const ntype* parent_type, std::string_view name, T(ClassT::* member));
    template <typename T, typename ClassT>
    nproperty(const ntype* parent_type, std::string_view name, const T& (ClassT::*getter)() const,
              void (ClassT::*setter)(const T&));

    nobject get(const nwrapper& instance) const;
    void set(const nwrapper& instance, const nwrapper& value) const;

    const class nclass* class_type() const;
    NTR_INLINE const ntype* property_type() const { return _property_type; }

private:
    const ntype* _property_type;
    std::function<nobject(const nwrapper&)> _getter;
    std::function<void(const nwrapper&, const nwrapper&)> _setter;
};

} // namespace ntr

#include "../impl/field/nproperty.inl"