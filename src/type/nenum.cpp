#include "../../inc/type/nenum.h"
#include "../../inc/field/neitem.h"

namespace ntr
{

nenum::nenum(std::string_view name) : ntype(etype::eenum, name)
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

const neitem* nenum::get_eitem(long value) const
{
    return _enum_field_map.at(value)->get();
}

const neitem* nenum::get_eitem(std::string_view name) const
{
    return _str_field_map.at(std::string_view(name))->get();
}

} // namespace ntr
