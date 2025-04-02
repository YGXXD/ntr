#pragma once

#include "nclass.h"
#include "../field/nfunction.h"
#include "../field/nproperty.h"

namespace ntr
{

// construct
inline nclass::nclass(std::string_view name) : ntype(etype::eclass, name)
{
}

// logic
inline void nclass::add_function(std::unique_ptr<nfunction>&& function)
{
    if (_field_map.find(function.get()->name()) == _field_map.end())
    {
        _functions.push_back(std::move(function));
        auto function = --_functions.end();
        _field_map.insert({ function->get()->name(), { function, _properties.end() } });
    }
}

inline void nclass::add_property(std::unique_ptr<nproperty>&& property)
{
    if (_field_map.find(property.get()->name()) == _field_map.end())
    {
        _properties.push_back(std::move(property));
        auto property = --_properties.end();
        _field_map.insert({ property->get()->name(), { _functions.end(), property } });
    }
}

inline void nclass::remove(std::string_view name)
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

inline const struct nfunction* nclass::get_function(std::string_view name) const
{
    auto function = _field_map.at(name).first;
    if (function == _functions.end())
        std::__throw_out_of_range("unordered_map::at: key not found");
    return function->get();
}

inline const struct nproperty* nclass::get_property(std::string_view name) const
{
    auto property = _field_map.at(name).second;
    if (property == _properties.end())
        std::__throw_out_of_range("unordered_map::at: key not found");
    return property->get();
}

} // namespace ntr