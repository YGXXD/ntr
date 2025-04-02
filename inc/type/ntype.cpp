#include "ntype.h"
#include "nnumeric.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

ntype::ntype(etype kind, std::string_view name) : _kind(kind), _name(name)
{
}

const nnumeric* ntype::as_numeric() const
{
    return is_numeric() ? static_cast<const nnumeric*>(this) : nullptr;
}

const nenum* ntype::as_enum() const
{
    return is_enum() ? static_cast<const nenum*>(this) : nullptr;
}

const nclass* ntype::as_class() const
{
    return is_class() ? static_cast<const nclass*>(this) : nullptr;
}

} // namespace ntr
