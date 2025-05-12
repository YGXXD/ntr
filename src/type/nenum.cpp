//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/nenum.hpp"
#include "implement.hpp"

namespace ntr
{

nenum::enum_integer_type nenum::get_value(const nobject& enum_)
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

void nenum::set_value(nobject& enum_, enum_integer_type value)
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
nenum::nenum(std::string_view name, uint32_t size, uint32_t align, operations* ops)
    : ntype(etype::eenum, size, align, ops, name)
{
}

void nenum::add_eitem(std::unique_ptr<neitem>&& item)
{
    if (_str_field_map.find(item.get()->name()) == _str_field_map.end())
    {
        _items.push_back(std::move(item));
        auto item_it = --_items.end();
        _str_field_map.insert({ item_it->get()->name(), item_it });
        _enum_field_map.insert({ item_it->get()->value(), item_it });
    }
}

void nenum::remove_eitem(std::string_view name)
{
    if (_str_field_map.find(name) != _str_field_map.end())
    {
        auto item = _str_field_map.at(name);
        _str_field_map.erase(item->get()->name());
        _enum_field_map.erase(item->get()->value());
        _items.erase(item);
    }
}

const neitem* nenum::get_eitem(enum_integer_type value) const
{
    return _enum_field_map.at(value)->get();
}

const neitem* nenum::get_eitem(std::string_view name) const
{
    return _str_field_map.at(std::string_view(name))->get();
}

} // namespace ntr
