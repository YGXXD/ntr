#pragma once

#include "ntype.h"

namespace ntr
{

class nclass : public ntype
{
public:
    nclass(std::string_view name);

    void add_function(std::unique_ptr<class nfunction>&& function);
    void add_property(std::unique_ptr<class nproperty>&& property);

    void remove(std::string_view name);

    const nfunction* get_function(std::string_view name) const;
    const nproperty* get_property(std::string_view name) const;

private:
    std::list<std::unique_ptr<nfunction>> _functions;
    std::list<std::unique_ptr<nproperty>> _properties;

    std::unordered_map<std::string_view,
                       std::pair<std::list<std::unique_ptr<nfunction>>::const_iterator,
                                 std::list<std::unique_ptr<nproperty>>::const_iterator>>
        _field_map;
};

} // namespace ntr