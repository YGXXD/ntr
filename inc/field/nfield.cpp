#include "nfield.h"

namespace ntr
{

nfield::nfield(const struct ntype* parent_type, efield kind, std::string_view name)
    : _parent_type(parent_type), _kind(kind), _name(name)
{
}

} // namespace ntr
