#pragma once

#include "ntype.h"
#include "../field/nproperty.h"
#include "../field/nfunction.h"

namespace ntr
{

struct nclass : ntype
{
    nclass(std::string_view name);

    template <etype E, typename T>
    friend struct nfactory;

    const nfunction& get_function(std::string_view name) const;
    const nproperty& get_property(std::string_view name) const;

private:
    template <typename F>
    void add_function(std::string_view name, F fun);

    template <typename M>
    void add_property(std::string_view name, M member);
    template <typename Get, typename Set>
    void add_property(std::string_view name, Get getter, Set setter);

    void remove(std::string_view name);

    std::vector<nfunction> _functions;
    std::vector<nproperty> _properties;
};

} // namespace ntr