#pragma once

#include "nclass.h"

namespace ntr
{

// construct
inline nclass::nclass(std::string_view name) : ntype(etype::eclass, name)
{
}

} // namespace ntr