#include "../../inc/field/neitem.h"

namespace ntr
{

neitem::neitem(ntype* parent_type, std::string_view name, long value)
    : nfield(parent_type, efield::eeitem, name), _value(value)
{
}

} // namespace ntr
