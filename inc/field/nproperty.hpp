#pragma once

#include "nfield.hpp"
#include "../core/nobject.hpp"
#include "../core/nreference.hpp"

namespace ntr
{

class NTR_API nproperty : public nfield
{
public:
    nproperty(ntype* parent_type, std::string_view name);
    template <typename T, typename ClassT>
    nproperty(ntype* parent_type, std::string_view name, T(ClassT::* member));
    template <typename T, typename ClassT>
    nproperty(ntype* parent_type, std::string_view name, T (ClassT::*getter)() const,
              void (ClassT::*setter)(const T&));

    nobject get(const nreference& instance) const;
    void set(const nreference& instance, const nreference& value) const;

    const class nclass* class_type() const;
    NTR_INLINE const ntype* property_type() const { return _property_type; }

private:
    const ntype* _property_type;
    std::function<nobject(const nreference&)> _getter;
    std::function<void(const nreference&, const nreference&)> _setter;
};

} // namespace ntr