#include "../../inc/type/ntype.hpp"
#include "../../inc/type/nnumeric.hpp"
#include "../../inc/type/nenum.hpp"
#include "../../inc/type/nclass.hpp"
#include "../../inc/type/npointer.hpp"

namespace ntr
{

ntype::ntype(etype kind, uint32_t size, uint32_t align, operations* ops,
             std::string_view name)
    : _kind(kind), _is_registered(false), _size(size), _align(align), _ops(ops),
      _name(name)
{
}

void ntype::set_name(std::string_view name)
{
    if (is_registered())
        throw std::logic_error("ntype::set_name : type is already registered");
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
    return std::move(nobject(this).alloc().init());
}

nobject ntype::object_copy(const nwrapper& wrapper) const
{
    if (wrapper.type() != this)
        throw std::invalid_argument(
            "ntype::object_copy : wrapper's type is different from this");
    return std::move(nobject(this).alloc().init_copy(wrapper.data()));
}

nobject ntype::object_move(const nwrapper& wrapper) const
{
    if (wrapper.type() != this)
        throw std::invalid_argument(
            "ntype::object_move : wrapper's type is different from this");
    return std::move(nobject(this).alloc().init_move(wrapper.data()));
}

} // namespace ntr
