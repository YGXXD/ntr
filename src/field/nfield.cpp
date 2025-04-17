#include "../../inc/field/nfield.hpp"

namespace ntr
{

nfield::nfield(const class ntype* parent_type, efield kind, std::string_view name)
    : _kind(kind), _name(name), _parent_type(parent_type)
{
}

} // namespace ntr
