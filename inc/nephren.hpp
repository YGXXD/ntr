#pragma once

#include "implement.hpp"
#include "core/nfactory.hpp"
#include "core/nregistrar.hpp"

namespace ntr
{

class nephren
{
public:
    static NTR_INLINE const ntype* get(std::string_view name)
    {
        return nregistrar::instance().get_type(name);
    }

    template <typename T>
    static NTR_INLINE const auto* get()
    {
        return nregistrar::get_type<T>();
    }

    template <typename T>
    static NTR_INLINE auto& type()
    {
        return nregistrar::factory_wrapper<T>();
    }

    template <typename T>
    static NTR_INLINE auto& type(std::string_view name)
    {
        return nregistrar::instance().regist<T>(name);
    }
};

} // namespace ntr