#include "ntype.h"
#include "nbasic.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

const nbasic* ntype::as_basic() const
{
    if (_kind == etype::ebasic)
        return static_cast<const nbasic*>(this);
    return nullptr;
}

const nenum* ntype::as_enum() const
{
    if (_kind == etype::eenum)
        return static_cast<const nenum*>(this);
    return nullptr;
}

const nclass* ntype::as_class() const
{
    if (_kind == etype::eclass)
        return static_cast<const nclass*>(this);
    return nullptr;
}

} // namespace ntr
