#include "nefuren.h"

namespace ntr
{

std::unordered_map<std::string_view, ntype*> nefuren::_type_map;

const ntype* nefuren::get_type(std::string_view name)
{
    auto it = _type_map.find(name);
    return it != _type_map.end() ? it->second : nullptr;
}

} // namespace ntr
