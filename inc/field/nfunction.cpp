#include "nfunction.h"

namespace ntr
{

nfunction::nfunction(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
}

} // namespace ntr
