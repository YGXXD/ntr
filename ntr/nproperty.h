#pragma once

#include <string_view>
#include "detail/function_traits.h"
#include "detail/property_traits.h"

namespace ntr
{

template <typename... Args>
struct property_impl;

template <typename P>
struct property_impl<P>
{
    using traits = detail::property_traits<P>;
    using cpp_class = typename traits::cpp_class;

    constexpr property_impl(std::string_view&& pname, P&& mptr) : name(pname), object_pointer(mptr) {}

    constexpr auto get_name() const { return name; }

    inline constexpr auto get(const cpp_class* obj) const { return (obj->*object_pointer); }

    inline void set(cpp_class* obj, const typename traits::type& value) const { (obj->*object_pointer) = value; }

private:
    std::string_view name;
    P object_pointer;
};

template <typename Get, typename Set>
struct property_impl<Get, Set>
{
    using getter_traits = detail::function_traits<Get>;
    using cpp_class = typename getter_traits::cpp_class;

    constexpr property_impl(std::string_view&& pname, Get&& getter, Set&& setter)
        : name(pname), getter_pointer(getter), setter_pointer(setter)
    {
    }

    constexpr auto get_name() const { return name; }

    inline constexpr auto get(const cpp_class* obj) const { return (obj->*getter_pointer)(); }

    inline void set(cpp_class* obj, const typename getter_traits::result& value) const
    {
        (obj->*setter_pointer)(value);
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