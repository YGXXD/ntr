#pragma once

#include "type/nfactory.h"
#include <unordered_map>

namespace ntr
{

struct nephren
{
private:
    nephren() = default;
    ~nephren() = default;

    static std::unordered_map<std::string_view, const ntype*> _type_map;

public:
    static const ntype* get_type(std::string_view name);

    template <typename T>
    static inline const ntype* get_type()
    {
        return factory<T>()._type.get();
    }

    template <typename T>
    static inline auto& factory()
    {
        return nfactory<ntype::to_etype<T>(), T>::instance();
    }

    template <typename T>
    static inline auto& regist(std::string_view name)
    {
        auto& fact = factory<T>();
        if (_type_map.find(name) != _type_map.end())
            std::__throw_logic_error("type already registered");
        fact._type->_name = name;
        _type_map.insert({ fact._type->name(), fact._type.get() });
        return fact;
    }
};

} // namespace ntr