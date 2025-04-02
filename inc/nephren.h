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
            std::__throw_logic_error((std::string("type \"") + std::string(name) +
                                      std::string("\" already registered"))
                                         .c_str());
        fact._type->set_name(name);
        _type_map.insert({ fact._type->name(), fact._type.get() });
        return fact;
    }

public:
    static const ntype* get_type(std::string_view name);

    template <typename T>
    static inline const ntype* get_type()
    {
        return factory<T>()._type.get();
    }

    template <typename T, typename = std::enable_if_t<ntype::is_class<T>()>>
    static inline auto& class_()
    {
        return factory<T>();
    }

    template <typename T, typename = std::enable_if_t<ntype::is_enum<T>()>>
    static inline auto& enum_()
    {
        return factory<T>();
    }

    template <typename T, typename = std::enable_if_t<ntype::is_numeric<T>()>>
    static inline auto& numeric_()
    {
        return factory<T>();
    }

    template <typename T, typename = std::enable_if_t<ntype::is_class<T>()>>
    static inline auto& class_(std::string_view name)
    {
        return regist<T>(name);
    }

    template <typename T, typename = std::enable_if_t<ntype::is_enum<T>()>>
    static inline auto& enum_(std::string_view name)
    {
        return regist<T>(name);
    }

    template <typename T, typename = std::enable_if_t<ntype::is_numeric<T>()>>
    static inline auto& numeric_(std::string_view name)
    {
        return regist<T>(name);
    }
};

} // namespace ntr