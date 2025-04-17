#include "../../inc/field/neitem.h"
#include "../../inc/type/nenum.h"

namespace ntr
{

neitem::neitem(ntype* parent_type, std::string_view name, long value)
    : nfield(parent_type, efield::eeitem, name), _value(value)
{
    if (parent_type->kind() != ntype::etype::eenum)
        throw std::invalid_argument("neitem must be created from an enum type");
}

const nenum* neitem::enum_type() const
{
    return static_cast<const nenum*>(parent_type());
}

} // namespace ntr
