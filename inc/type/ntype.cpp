#include "ntype.h"
#include "nnumeric.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

bool ntype::is_unknown() const
{
    return _kind == etype::eunknown;
}

bool ntype::is_numeric() const
{
    return _kind == etype::enumeric;
}

bool ntype::is_enum() const
{
    return _kind == etype::eenum;
}

bool ntype::is_class() const
{
    return _kind == etype::eclass;
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
