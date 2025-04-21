#include "../../inc/type/npointer.hpp"

namespace ntr
{

void* npointer::get_value(class nobject& pointer)
{
    if (!pointer.type()->is_pointer())
        throw std::runtime_error("npointer::get_value : type mismatch");
    return *reinterpret_cast<void**>(pointer.data());
}

void npointer::set_value(nobject& pointer, void* value)
{
    if (!pointer.type()->is_pointer())
        throw std::runtime_error("npointer::set_value : type mismatch");
    *reinterpret_cast<void**>(pointer.data()) = value;
}

nwrapper npointer::get_target(nobject& pointer)
{
    if (!pointer.type()->is_pointer())
        throw std::runtime_error("npointer::get_target : type mismatch");
    void* value = get_value(pointer);
    if (value == nullptr)
        throw std::runtime_error("npointer::get_target : value is nullptr");
    return nwrapper(pointer.type()->as_pointer()->pointed_type(), value);
}

npointer::npointer(uint8_t depth, const ntype* pointed_type, std::string_view name,
                   operations* ops)
    : ntype(ntype::etype::epointer, sizeof(void*), ops, name), _depth(depth),
      _pointed_type(pointed_type)
{
}

} // namespace ntr
