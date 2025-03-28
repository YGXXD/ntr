#pragma once

#include "ntype.h"

namespace ntr
{

struct nclass : ntype
{
    nclass(const std::string& name) : ntype(etype::eclass, name) {}
    nclass(std::string&& name) : ntype(etype::eclass, std::move(name)) {}
};

} // namespace ntr