//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/npointer.hpp"
#include "implement.hpp"

namespace ntr
{

void* npointer::get_value(const nobject& pointer)
{
    if (!pointer.type()->is_pointer())
        throw std::invalid_argument(
            "npointer::get_value : pointer's type is not pointer type");
    return *reinterpret_cast<void* const*>(pointer.data());
}

void npointer::set_value(nobject& pointer, void* value)
{
    if (!pointer.type()->is_pointer())
        throw std::invalid_argument(
            "npointer::set_value : pointer's type is not pointer type");
    *reinterpret_cast<void**>(pointer.data()) = value;
}

nobject npointer::get_target(const nobject& pointer)
{
    void* ptr = get_value(pointer);
    if (ptr == nullptr)
        throw std::invalid_argument("npointer::get_target : pointer's value is nullptr");
    const ntype* pointing_type = pointer.type()->as_pointer()->pointing_type();
    return pointing_type->new_reference(nwrapper(pointing_type, ptr));
}

npointer::npointer(uint8_t depth, bool pointing_is_const, const ntype* pointing_type,
                   std::string_view name, operations* ops)
    : ntype(ntype::etype::epointer, static_cast<uint32_t>(sizeof(void*)),
            static_cast<uint32_t>(alignof(void*)), ops, name),
      _depth(depth), _pointing_is_const(pointing_is_const), _pointing_type(pointing_type)
{
}

} // namespace ntr
