#include "../../inc/type/ntype.hpp"
#include "../../inc/type/nnumeric.hpp"
#include "../../inc/type/nenum.hpp"
#include "../../inc/type/nclass.hpp"
#include "../../inc/type/npointer.hpp"

namespace ntr
{

ntype::ntype(etype kind, uint32_t size, operations* ops, std::string_view name)
    : _kind(kind), _is_registered(false), _size(size), _ops(ops), _name(name)
{
}

void ntype::set_name(std::string_view name)
{
    _name = name;
    _is_registered = true;
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

const npointer* ntype::as_pointer() const
{
    return is_pointer() ? static_cast<const npointer*>(this) : nullptr;
}

nobject ntype::object_new() const
{
    return nobject::new_init(this);
}

nobject ntype::object_clone(const nwrapper& wrapper) const
{
    if (wrapper.type() != this)
        throw std::runtime_error("ntype::object_clone : type mismatch");
    return nobject::new_clone(this, wrapper.data());
}

nobject ntype::object_steal(const nwrapper& wrapper) const
{
    if (wrapper.type() != this)
        throw std::runtime_error("ntype::object_steal : type mismatch");
    return nobject::new_steal(this, wrapper.data());
}

} // namespace ntr
