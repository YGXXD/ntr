//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/nclass.hpp"
#include "field/nfunction.hpp"
#include "field/nproperty.hpp"

namespace ntr
{

nclass::nclass(uint32_t size, uint32_t align, operations* ops, std::string_view name)
    : ntype(etype::eclass, size, align, ops, name)
{
}

nclass::~nclass() = default;

void nclass::add_function(std::unique_ptr<nfunction>&& function)
{
    if (!_field_map.contains(function->name()))
    {
        _field_map.insert({ function->name(), { function.get(), nullptr } });
        _functions.push_back(std::move(function));
    }
}

void nclass::add_property(std::unique_ptr<nproperty>&& property)
{
    if (!_field_map.contains(property->name()))
    {
        _field_map.insert({ property->name(), { nullptr, property.get() } });
        _properties.push_back(std::move(property));
    } // namespace ntr
}

void nclass::add_base_type(const nclass* base_type, ptrdiff_t offset)
{
    if (std::find_if(_base_type_pairs.begin(), _base_type_pairs.end(),
                     [base_type](const auto& base_type_pair)
    { return base_type_pair.first == base_type; }) == _base_type_pairs.end())
        _base_type_pairs.push_back({ base_type, offset });
}

void nclass::remove_field(std::string_view name)
{
    auto it = _field_map.find(name);
    if (it != _field_map.end())
    {
        if (it->first != nullptr)
            _functions.erase(std::find_if(_functions.begin(), _functions.end(),
                                          [&it](const auto& function)
            { return it->second.first == function.get(); }));
        else
            _properties.erase(std::find_if(_properties.begin(), _properties.end(),
                                           [&it](const auto& property)
            { return it->second.second == property.get(); }));
        _field_map.remove(it);
    }
}

const nfunction* nclass::get_function(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end() || !field_it->second.first)
    {
        for (auto& base_type_pair : _base_type_pairs)
        {
            if (const nfunction* function = base_type_pair.first->get_function(name))
                return function;
        }
        return nullptr;
    }
    return field_it->second.first;
}

const nproperty* nclass::get_property(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end() || !field_it->second.second)
    {
        for (auto& base_type_pair : _base_type_pairs)
        {
            if (const nproperty* property = base_type_pair.first->get_property(name))
                return property;
        }
        return nullptr;
    }
    return field_it->second.second;
}

void* nclass::cast_to(const nclass* type, void* pointer) const
{
    if (type)
    {
        if (type == this)
            return pointer;
        ptrdiff_t offset;
        if (check_base_type(type, &offset))
            return static_cast<void*>(static_cast<char*>(pointer) + offset);
        if (type->check_base_type(this, &offset))
            return static_cast<void*>(static_cast<char*>(pointer) - offset);
    }
    return nullptr;
}

bool nclass::has_base_type(const nclass* type) const
{
    return type && check_base_type(type, nullptr);
}

bool nclass::has_function(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end())
        return false;
    return field_it->second.first != nullptr;
}

bool nclass::has_property(std::string_view name) const
{
    auto field_it = _field_map.find(name);
    if (field_it == _field_map.end())
        return false;
    return field_it->second.second != nullptr;
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

bool nclass::check_base_type(const nclass* type, ptrdiff_t* out_offset) const
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
        if (base_type_pair.first->check_base_type(type, &offset))
        {
            if (out_offset)
                *out_offset = base_type_pair.second + offset;
            return true;
        }
    }
    return false;
}

} // namespace ntr