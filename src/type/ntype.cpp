#include "../../inc/type/ntype.hpp"
#include "../../inc/type/nnumeric.hpp"
#include "../../inc/type/nenum.hpp"
#include "../../inc/type/nclass.hpp"

namespace ntr
{

ntype::ntype(etype kind, uint32_t size, operations* ops, std::string_view name)
    : _kind(kind), _size(size), _ops(ops), _name(name)
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

nobject ntype::object_new() const
{
    return nobject::new_(this);
}

nobject ntype::object_copy(const void* const data) const
{
    return nobject::new_copy_(this, data);
}

nobject ntype::object_steal(void* data) const
{
    return nobject::new_steal_(this, data);
}

} // namespace ntr
