//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/ntype.hpp"
#include "type/nnumeric.hpp"
#include "type/nenum.hpp"
#include "type/nclass.hpp"
#include "type/npointer.hpp"

namespace ntr
{

ntype::ntype(etype kind, uint32_t size, uint32_t align, operations* ops,
             std::string_view name)
    : _kind(kind), _is_registered(false), _size(size), _align(align), _ops(ops),
      _name_size(), _name(nullptr)
{
}

ntype::~ntype()
{
    if (_name)
        delete[] _name;
};

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

nobject ntype::new_instance() const
{
    return std::move(nobject(this, nobject::eobject::eobtain).alloc().init());
}

nobject ntype::new_instance(const nwrapper& wrapper) const
{
    if (wrapper.type() != this)
        throw std::invalid_argument(
            "ntype::new_instance : wrapper's type is different from this");
    return std::move(nobject(this, nobject::eobject::eobtain).alloc().init_copy(wrapper));
}

nobject ntype::new_instance_rv(const nwrapper& wrapper) const
{
    if (wrapper.type() != this)
        throw std::invalid_argument(
            "ntype::new_instance_rv : wrapper's type is different from this");
    return std::move(nobject(this, nobject::eobject::eobtain).alloc().init_move(wrapper));
}

nobject ntype::new_reference(const nwrapper& wrapper) const
{
    if (wrapper.type() != this)
        throw std::invalid_argument(
            "ntype::new_reference : wrapper's type is different from this");
    return std::move(nobject(this, nobject::eobject::eref).hold_ref(wrapper));
}

void ntype::regist(std::string_view name)
{
    if (is_registered())
        throw std::logic_error("ntype::set_name : type is already registered");
    _name_size = name.size();
    _name = new char[_name_size + 1];
    memcpy(_name, name.data(), _name_size);
    _name[_name_size] = '\0';
    _is_registered = true;
}

} // namespace ntr
