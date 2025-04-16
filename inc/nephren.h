#pragma once

#include "core/nfactory.h"
#include "core/nregistrar.h"

// impl
#include "field/nproperty.inl"
#include "field/nfunction.inl"
#include "core/nfactory.inl"
#include "core/nregistrar.inl"
#include "core/nobject.inl"
#include "core/nreference.inl"

namespace ntr
{

class nephren
{
public:
    static NTR_INLINE const ntype* get_type(std::string_view name)
    {
        return nregistrar::instance().get_type(name);
    }

    template <typename T>
    static NTR_INLINE const ntype* get_type()
    {
        return nregistrar::get_type<T>();
    }

    template <typename T, typename = std::enable_if_t<is_etype_class<T>()>>
    static NTR_INLINE auto& class_()
    {
        return nregistrar::factory_wrapper<T>();
    }

    template <typename T, typename = std::enable_if_t<is_etype_enum<T>()>>
    static NTR_INLINE auto& enum_()
    {
        return nregistrar::factory_wrapper<T>();
    }

    template <typename T, typename = std::enable_if_t<is_etype_numeric<T>()>>
    static NTR_INLINE auto& numeric_()
    {
        return nregistrar::factory_wrapper<T>();
    }

    template <typename T, typename = std::enable_if_t<is_etype_class<T>()>>
    static NTR_INLINE auto& class_(std::string_view name)
    {
        return nregistrar::instance().regist<T>(name);
    }

    template <typename T, typename = std::enable_if_t<is_etype_enum<T>()>>
    static NTR_INLINE auto& enum_(std::string_view name)
    {
        return nregistrar::instance().regist<T>(name);
    }

    template <typename T, typename = std::enable_if_t<is_etype_numeric<T>()>>
    static NTR_INLINE auto& numeric_(std::string_view name)
    {
        return nregistrar::instance().regist<T>(name);
    }
};

} // namespace ntr