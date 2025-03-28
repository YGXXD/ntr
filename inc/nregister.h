#pragma once

#include <unordered_map>
#include "nfactory.h"

namespace ntr
{

struct nregister
{
private:
    template <etype E>
    struct type_map_wrapper
    {
        static inline type_map_wrapper& instance()
        {
            static type_map_wrapper _instance;
            return _instance;
        }

        inline void insert(std::string_view name, ntype* type)
        {
            _type_map.insert({ name, type });
        }

        inline ntype* get(std::string_view name) const
        {
            auto it = _type_map.find(name);
            return it != _type_map.end() ? it->second : nullptr;
        }

        inline void remove(std::string_view name) { _type_map.erase(name); }

    private:
        type_map_wrapper() = default;
        ~type_map_wrapper() = default;

        std::unordered_map<std::string_view, ntype*> _type_map;
    };

    nregister() = default;
    ~nregister() = default;

    template <typename T>
    static inline constexpr etype cast_etype()
    {
        if constexpr (std::is_fundamental_v<T>)
            return etype::ebasic;
        else if constexpr (std::is_enum_v<T>)
            return etype::eenum;
        else if constexpr (std::is_class_v<T>)
            return etype::eclass;
        else
            static_assert(false, "unknown type");
    }

    template <typename T>
    static inline auto& get_factory()
    {
        return nfactory<cast_etype<T>(), T>::instance();
    }

    template <typename T>
    static inline auto& get_type_map_wrapper()
    {
        return type_map_wrapper<cast_etype<T>()>::instance();
    }

public:
    static inline const ntype* get_type(etype kind, const std::string& name)
    {
        switch (kind)
        {
        case etype::ebasic:
            return type_map_wrapper<etype::ebasic>::instance().get(name);
        case etype::eenum:
            return type_map_wrapper<etype::eenum>::instance().get(name);
        case etype::eclass:
            return type_map_wrapper<etype::eclass>::instance().get(name);
        default:
            return nullptr;
        }
    }

    template <typename T>
    static inline const ntype* get_type()
    {
        return get_factory<T>()._type.get();
    }

    template <typename T>
    static inline auto& regist(const std::string& name)
    {
        auto& factory = get_factory<T>();
        if (factory._type == nullptr)
        {
            factory.init(name);
            get_type_map_wrapper<T>().insert(factory._type->name(), factory._type.get());
        }
        return factory;
    }

    template <typename T>
    static inline void unregist()
    {
        auto& factory = get_factory<T>();
        if (factory._type != nullptr)
        {
            get_type_map_wrapper<T>().remove(factory._type->name());
            factory._type.reset();
        }
    }
};

} // namespace ntr