#include "../../inc/field/neitem.hpp"
#include "../../inc/implement.hpp"

namespace ntr
{

neitem::neitem(ntype* parent_type, std::string_view name, long value)
    : nfield(parent_type, efield::eeitem, name), _value(value)
{
    if (parent_type->kind() != ntype::etype::eenum)
        throw std::invalid_argument("neitem::neitem : parent type is not enum type");
}

const nenum* neitem::enum_type() const
{
    return static_cast<const nenum*>(parent_type());
}

} // namespace ntr
