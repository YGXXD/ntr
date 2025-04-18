#include "../../inc/type/nenum.hpp"
#include "../../inc/field/neitem.hpp"

namespace ntr
{

nenum::enum_integer_type nenum::get_value(class nobject& obj)
{
    if (!obj.type()->is_enum())
        throw std::runtime_error("nenum::get_value : type mismatch");
    switch (obj.type()->size())
    {
    case 1:
        return static_cast<enum_integer_type>(*reinterpret_cast<int8_t*>(obj.data()));
    case 2:
        return static_cast<enum_integer_type>(*reinterpret_cast<int16_t*>(obj.data()));
    case 4:
        return static_cast<enum_integer_type>(*reinterpret_cast<int32_t*>(obj.data()));
    case 8:
        return static_cast<enum_integer_type>(*reinterpret_cast<int64_t*>(obj.data()));
    default:
        throw std::runtime_error("nenum::get_value : size mismatch");
    }
}

void nenum::set_value(nobject& obj, enum_integer_type value)
{
    if (!obj.type()->is_enum())
        throw std::runtime_error("nenum::set_value : type mismatch");
    switch (obj.type()->size())
    {
    case 1:
        *reinterpret_cast<int8_t*>(obj.data()) = static_cast<int8_t>(value);
        break;
    case 2:
        *reinterpret_cast<int16_t*>(obj.data()) = static_cast<int16_t>(value);
        break;
    case 4:
        *reinterpret_cast<int32_t*>(obj.data()) = static_cast<int32_t>(value);
        break;
    case 8:
        *reinterpret_cast<int64_t*>(obj.data()) = static_cast<int64_t>(value);
        break;
    }
}
nenum::nenum(std::string_view name, uint32_t size, operations* ops)
    : ntype(etype::eenum, size, ops, name)
{
}

void nenum::add_eitem(std::unique_ptr<neitem>&& item)
{
    if (_str_field_map.find(item.get()->name()) == _str_field_map.end())
    {
        _items.push_back(std::move(item));
        auto item = --_items.end();
        _str_field_map.insert({ item->get()->name(), item });
        _enum_field_map.insert({ item->get()->value(), item });
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
