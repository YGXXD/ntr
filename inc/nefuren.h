#pragma once

#include "type/nfactory.h"
#include <cassert>
#include <unordered_map>

namespace ntr
{

struct nefuren
{
private:
    nefuren() = default;
    ~nefuren() = default;

    static std::unordered_map<std::string_view, ntype*> _type_map;

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
        assert(_type_map.find(name) == _type_map.end());
        assert(fact._type == nullptr);
        fact.init(name);
        _type_map.insert({ fact._type->name(), fact._type.get() });
        return fact;
    }

    template <typename T>
    static inline void unregist()
    {
        auto& fact = factory<T>();
        if (fact._type != nullptr)
        {
            _type_map.erase(fact._type->name());
            fact._type.reset();
        }
    }
};

} // namespace ntr