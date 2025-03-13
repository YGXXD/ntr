#pragma once

#include <string_view>
#include "detail/function_traits.h"

namespace ntr
{

template <typename Impl, typename T>
struct iproperty
{
    inline constexpr auto get_name() const { return static_cast<const Impl*>(this)->get_name_impl(); }
};

template <typename Impl, typename ClassT, typename T>
struct iproperty<Impl, T ClassT::*> : iproperty<Impl, void>
{
    inline constexpr T get(const ClassT* instance) const { return static_cast<const Impl*>(this)->get_impl(instance); }

    inline constexpr void set(ClassT* instance, T&& value) const
    {
        static_cast<const Impl*>(this)->set_impl(instance, std::forward<T>(value));
    }
};

template <typename... Args>
struct property_impl;

template <typename P>
struct property_impl<P> : iproperty<property_impl<P>, P>
{
    template <typename Impl, typename T>
    friend struct iproperty;

    constexpr property_impl(std::string_view&& pname, P&& mptr) : name(pname), object_pointer(mptr) {}

private:
    constexpr auto get_name_impl() const { return name; }

    template <typename ClassT>
    inline constexpr auto get_impl(ClassT&& instance) const
    {
        return (std::forward<ClassT>(instance)->*object_pointer);
    }

    template <typename ClassT, typename T>
    inline void set_impl(ClassT&& instance, T&& value) const
    {
        (std::forward<ClassT>(instance)->*object_pointer) = std::forward<T>(value);
    }

    std::string_view name;
    P object_pointer;
};

template <typename Get, typename Set>
struct property_impl<Get, Set>
    : iproperty<property_impl<Get, Set>,
                typename detail::function_traits<Get>::result detail::function_traits<Get>::cpp_class::*>
{
    template <typename Impl, typename T>
    friend struct iproperty;

    constexpr property_impl(std::string_view&& pname, Get&& getter, Set&& setter)
        : name(pname), getter_pointer(getter), setter_pointer(setter)
    {
    }

private:
    constexpr auto get_name_impl() const { return name; }

    template <typename ClassT>
    inline constexpr auto get_impl(ClassT&& instance) const
    {
        return (std::forward<ClassT>(instance)->*getter_pointer)();
    }

    template <typename ClassT, typename T>
    inline void set_impl(ClassT&& instance, T&& value) const
    {
        (std::forward<ClassT>(instance)->*setter_pointer)(std::forward<T>(value));
    }

private:
    std::string_view name;
    Get getter_pointer;
    Set setter_pointer;
};

template <typename ClassT, typename T>
constexpr auto nproperty(std::string_view property_name, T ClassT::*&& object_pointer)
{
    return property_impl<T ClassT::*> { std::forward<std::string_view>(property_name),
                                        std::forward<T ClassT::*&&>(object_pointer) };
}

template <typename ClassT, typename T>
constexpr auto nproperty(std::string_view property_name, T (ClassT::*&& getter)() const,
                         void (ClassT::*&& setter)(const T&))
{
    return property_impl<T (ClassT::*)() const, void (ClassT::*)(const T&)> {
        std::forward<std::string_view>(property_name), std::forward<T (ClassT::*)() const>(getter),
        std::forward<void (ClassT::*)(const T&)>(setter)
    };
}

} // namespace ntr