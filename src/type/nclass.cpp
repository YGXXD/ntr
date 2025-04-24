#include "../../inc/type/nclass.hpp"
#include "../../inc/implement.hpp"

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
        auto function = --_functions.end();
        _field_map.insert({ function->get()->name(), { function, _properties.end() } });
    }
}

void nclass::add_property(std::unique_ptr<nproperty>&& property)
{
    if (_field_map.find(property.get()->name()) == _field_map.end())
    {
        _properties.push_back(std::move(property));
        auto property = --_properties.end();
        _field_map.insert({ property->get()->name(), { _functions.end(), property } });
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
    auto function = _field_map.at(name).first;
    if (function == _functions.end())
        throw std::out_of_range("unordered_map::at: key not found");
    return function->get();
}

const nproperty* nclass::get_property(std::string_view name) const
{
    auto property = _field_map.at(name).second;
    if (property == _properties.end())
        throw std::out_of_range("unordered_map::at: key not found");
    return property->get();
}

} // namespace ntr