//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/npointer.hpp"
#include "type/nclass.hpp"
#include "core/ntype_ops_factory.hpp"

namespace ntr
{

void* npointer::get_value(const nobject& pointer)
{
    if (!pointer.type()->is_pointer())
        throw std::invalid_argument(
            "npointer::get_value : pointer's type is not pointer type");
    return *static_cast<void* const*>(pointer.data());
}

void npointer::set_value(nobject& pointer, void* value)
{
    if (!pointer.type()->is_pointer())
        throw std::invalid_argument(
            "npointer::set_value : pointer's type is not pointer type");
    *static_cast<void**>(pointer.data()) = value;
}

npointer::npointer(const ntype* dereference_type)
    : ntype(ntype::etype::epointer, static_cast<uint32_t>(sizeof(void*)),
            static_cast<uint32_t>(alignof(void*)),
            &ntype_ops_factory<void*>::instance().ops),
      _dereference_type(dereference_type)
{
}

nobject npointer::dereference(const nwrapper& pointer) const
{
    void* ptr_value = *static_cast<void**>(pointer.data());
    if (pointer.type() != this)
    {
        const npointer* pointer_type = pointer.type()->as_pointer();
        const nclass* pointer_dereference_type =
            pointer_type ? pointer_type->_dereference_type->as_class() : nullptr;
        ptr_value = pointer_dereference_type
                        ? pointer_dereference_type->cast_to(_dereference_type->as_class(),
                                                            ptr_value)
                        : nullptr;
    }
    if (!ptr_value)
        throw std::invalid_argument("npointer::dereference : pointer deference failed");
    return _dereference_type->new_reference(nwrapper(_dereference_type, ptr_value));
}

npointer::~npointer() = default;

} // namespace ntr
