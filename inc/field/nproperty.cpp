#include "nproperty.h"

namespace ntr
{

nproperty::nproperty(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
}

} // namespace ntr
