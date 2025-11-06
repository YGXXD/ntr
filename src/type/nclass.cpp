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

void nclass::add_base_type(const nclass* base_type, ptrdiff_t offset)
{
    if (std::find_if(_base_type_pairs.begin(), _base_type_pairs.end(),
                     [base_type](const auto& base_type_pair)
    { return base_type_pair.first == base_type; }) == _base_type_pairs.end())
        _base_type_pairs.push_back(std::make_pair(base_type, offset));
}

void nclass::remove_field(std::string_view name)
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
    if (field_it == _field_map.end() || field_it->second.first == _functions.end())
    {
        for (auto& base_type_pair : _base_type_pairs)
        {
            if (const nfunction* function = base_type_pair.first->get_function(name))
                return function;
        }
        return nullptr;
    }
    return field_it->second.first->get();
}

const nproperty* nclass::get_property(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end() || field_it->second.second == _properties.end())
    {
        for (auto& base_type_pair : _base_type_pairs)
        {
            if (const nproperty* property = base_type_pair.first->get_property(name))
                return property;
        }
        return nullptr;
    }
    return field_it->second.second->get();
}

void* nclass::cast_to(const nclass* type, void* pointer) const
{
    if (type)
    {
        ptrdiff_t offset;
        if (has_base_type(type, &offset))
            return static_cast<void*>(static_cast<char*>(pointer) + offset);
    }
    return nullptr;
}

bool nclass::has_base_type(const nclass* type, ptrdiff_t* out_offset) const
{
    auto it = std::find_if(_base_type_pairs.begin(), _base_type_pairs.end(),
                           [type](const auto& base_type_pair)
    { return base_type_pair.first == type; });
    if (it != _base_type_pairs.end())
    {
        if (out_offset)
            *out_offset = it->second;
        return true;
    }
    for (auto& base_type_pair : _base_type_pairs)
    {
        ptrdiff_t offset;
        if (base_type_pair.first->has_base_type(type, &offset))
        {
            if (out_offset)
                *out_offset = base_type_pair.second + offset;
            return true;
        }
    }
    return false;
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