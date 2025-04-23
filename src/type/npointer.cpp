#include "../../inc/type/npointer.hpp"

namespace ntr
{

void* npointer::get_value(class nobject& pointer)
{
    if (!pointer.type()->is_pointer())
        throw std::invalid_argument(
            "npointer::get_value : pointer's type is not pointer type");
    return *reinterpret_cast<void**>(pointer.data());
}

void npointer::set_value(nobject& pointer, void* value)
{
    if (!pointer.type()->is_pointer())
        throw std::invalid_argument(
            "npointer::set_value : pointer's type is not pointer type");
    *reinterpret_cast<void**>(pointer.data()) = value;
}

nwrapper npointer::get_target(nobject& pointer)
{
    if (!pointer.type()->is_pointer())
        throw std::invalid_argument(
            "npointer::get_target : pointer's type is not pointer type");
    void* value = get_value(pointer);
    if (value == nullptr)
        throw std::invalid_argument("npointer::get_target : pointer's value is nullptr");
    return nwrapper(pointer.type()->as_pointer()->pointed_type(), value);
}

npointer::npointer(uint8_t depth, const ntype* pointed_type, std::string_view name,
                   operations* ops)
    : ntype(ntype::etype::epointer, sizeof(void*), alignof(void*), ops, name),
      _depth(depth), _pointed_type(pointed_type)
{
}

} // namespace ntr
