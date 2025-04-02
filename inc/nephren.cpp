#include "nephren.h"

namespace ntr
{

std::unordered_map<std::string_view, const ntype*> nephren::_type_map;

const ntype* nephren::get_type(std::string_view name)
{
    auto it = _type_map.find(name);
    if (it == _type_map.end())
        throw std::logic_error((std::string("type \"") + std::string(name) +
                                  std::string("\" not registered"))
                                     .c_str());
    return it->second;
}

} // namespace ntr
