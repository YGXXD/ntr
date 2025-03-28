#pragma once

#include <unordered_map>
#include "nfactory.h"

namespace ntr
{

struct nefuren
{
private:
    nefuren() = default;
    ~nefuren() = default;

    template <typename T>
    static inline auto& get_factory()
    {
        return nfactory<cast_etype<T>(), T>::instance();
    }

    static std::unordered_map<std::string_view, ntype*> _type_map;

public:
    static inline const ntype* get_type(std::string_view name)
    {
        auto it = _type_map.find(name);
        return it != _type_map.end() ? it->second : nullptr;
    }

    template <typename T>
    static inline const ntype* get_type()
    {
        return get_factory<T>()._type.get();
    }

    template <typename T>
    static inline auto& regist(std::string_view name)
    {
        auto& factory = get_factory<T>();
        if (factory._type == nullptr)
        {
            factory.init(name);
            _type_map.insert({ factory._type->name(), factory._type.get() });
        }
        return factory;
    }

    template <typename T>
    static inline void unregist()
    {
        auto& factory = get_factory<T>();
        if (factory._type != nullptr)
        {
            _type_map.erase(factory._type->name());
            factory._type.reset();
        }
    }
};

} // namespace ntr