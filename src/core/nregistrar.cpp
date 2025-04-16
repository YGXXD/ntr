#include "../../inc/core/nregistrar.h"

namespace ntr
{

const ntype* nregistrar::get_type(std::string_view name)
{
    auto it = _type_map.find(name);
    if (it == _type_map.end())
        throw std::logic_error((std::string("type \"") + std::string(name) +
                                std::string("\" not registered"))
                                   .c_str());
    return it->second;
}

void nregistrar::regist(std::string_view name, ntype* type)
{
    if (_type_map.find(name) != _type_map.end())
        throw std::logic_error((std::string("type \"") + std::string(name) +
                                std::string("\" already registered"))
                                   .c_str());
    type->set_name(name);
    _type_map.insert({ type->name(), type });
}

} // namespace ntr