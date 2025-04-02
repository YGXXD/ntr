#include "nephren.h"

namespace ntr
{

std::unordered_map<std::string_view, const ntype*> nephren::_type_map;

const ntype* nephren::get_type(std::string_view name)
{
    auto it = _type_map.find(name);
    if (it == _type_map.end())
        std::__throw_logic_error("type not registered");
    return it->second;
}

} // namespace ntr
