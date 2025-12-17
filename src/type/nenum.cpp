//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/nenum.hpp"
#include "field/neitem.hpp"

namespace ntr
{

enum_integer_type nenum::get_value(const nwrapper& enum_)
{
    if (!enum_.type()->is_enum())
        throw std::invalid_argument("nenum::get_value : enum_'s type is not enum type");
    switch (enum_.type()->size())
    {
    case 1:
        return static_cast<enum_integer_type>(
            *reinterpret_cast<const int8_t*>(enum_.data()));
    case 2:
        return static_cast<enum_integer_type>(
            *reinterpret_cast<const int16_t*>(enum_.data()));
    case 4:
        return static_cast<enum_integer_type>(
            *reinterpret_cast<const int32_t*>(enum_.data()));
    case 8:
        return static_cast<enum_integer_type>(
            *reinterpret_cast<const int64_t*>(enum_.data()));
    default:
        throw std::runtime_error("nenum::get_value : size mismatch");
    }
}

void nenum::set_value(nwrapper& enum_, enum_integer_type value)
{
    if (!enum_.type()->is_enum())
        throw std::invalid_argument("nenum::set_value : enum_'s type is not enum type");
    switch (enum_.type()->size())
    {
    case 1:
        *reinterpret_cast<int8_t*>(enum_.data()) = static_cast<int8_t>(value);
        break;
    case 2:
        *reinterpret_cast<int16_t*>(enum_.data()) = static_cast<int16_t>(value);
        break;
    case 4:
        *reinterpret_cast<int32_t*>(enum_.data()) = static_cast<int32_t>(value);
        break;
    case 8:
        *reinterpret_cast<int64_t*>(enum_.data()) = static_cast<int64_t>(value);
        break;
    }
}
nenum::nenum(uint16_t size, uint16_t align, operations* ops)
    : ntype(etype::eenum, size, align, ops)
{
}

nenum::~nenum() = default;

void nenum::add_eitem(std::unique_ptr<neitem>&& item)
{
    if (_str_field_map.find(item.get()->name()) == _str_field_map.end())
    {
        _str_field_map.insert({ item->name(), item.get() });
        _enum_field_map.insert({ item->value(), item.get() });
        _eitems.push_back(std::move(item));
    }
}

void nenum::remove_eitem(std::string_view name)
{
    auto it = _str_field_map.find(name);
    if (it != _str_field_map.end())
    {
        _str_field_map.remove(it->second->name());
        _enum_field_map.remove(it->second->value());
        _eitems.remove(std::find_if(_eitems.begin(), _eitems.end(),
                                    [&it](const auto& item)
        { return item.get() == it->second; }));
    }
}

const neitem* nenum::get_eitem(enum_integer_type value) const
{
    auto it = _enum_field_map.find(value);
    return it == _enum_field_map.end() ? nullptr : it->second;
}

const neitem* nenum::get_eitem(std::string_view name) const
{
    auto it = _str_field_map.find(name);
    return it == _str_field_map.end() ? nullptr : it->second;
}

bool nenum::has_eitem(std::string_view name) const
{
    return _str_field_map.contains(name);
}

bool nenum::has_eitem(enum_integer_type value) const
{
    return _enum_field_map.contains(value);
}

} // namespace ntr
