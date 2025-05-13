//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/nclass.hpp"

namespace ntr
{

nclass::nclass(std::string_view name, uint32_t size, uint32_t align, operations* ops)
    : ntype(etype::eclass, size, align, ops, name)
{
}

void nclass::add_function(std::unique_ptr<nfunction>&& function)
{
    if (_field_map.find(function.get()->name()) == _field_map.end())
    {
        _functions.push_back(std::move(function));
        auto function_it = --_functions.end();
        _field_map.insert(
            { function_it->get()->name(), { function_it, _properties.end() } });
    }
}

void nclass::add_property(std::unique_ptr<nproperty>&& property)
{
    if (_field_map.find(property.get()->name()) == _field_map.end())
    {
        _properties.push_back(std::move(property));
        auto property_it = --_properties.end();
        _field_map.insert(
            { property_it->get()->name(), { _functions.end(), property_it } });
    }
}

void nclass::remove(std::string_view name)
{
    if (_field_map.find(name) != _field_map.end())
    {
        auto field = _field_map.at(name);
        _field_map.erase(name);
        if (field.first != _functions.end())
            _functions.erase(field.first);
        else
            _properties.erase(field.second);
    }
}

const nfunction* nclass::get_function(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end())
        return nullptr;
    auto function_it = field_it->second.first;
    if (function_it == _functions.end())
        return nullptr;
    return function_it->get();
}

const nproperty* nclass::get_property(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end())
        return nullptr;
    auto property_it = field_it->second.second;
    if (property_it == _properties.end())
        return nullptr;
    return property_it->get();
}

bool nclass::has_function(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end())
        return false;
    return field_it->second.first != _functions.end();
}

bool nclass::has_property(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end())
        return false;
    return field_it->second.second != _properties.end();
}

nobject nclass::call(std::string_view name, const std::vector<nwrapper>& args) const
{
    return get_function(name)->call(args);
}

nobject nclass::get(std::string_view name, const nwrapper& instance) const
{
    return get_property(name)->get(instance);
}

void nclass::set(std::string_view name, const nwrapper& instance,
                 const nwrapper& value) const
{
    get_property(name)->set(instance, value);
}

} // namespace ntr