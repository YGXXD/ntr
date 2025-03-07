#pragma once

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

    constexpr property_impl(P&& p) : object_pointer(p) {}

    inline constexpr auto get(const cpp_class* obj) const { return (obj->*object_pointer); }

    inline void set(cpp_class* obj, const typename traits::type& value) const { (obj->*object_pointer) = value; }

private:
    P object_pointer;
};

template <typename Get, typename Set>
struct property_impl<Get, Set>
{
    using getter_traits = detail::function_traits<Get>;
    using cpp_class = typename getter_traits::cpp_class;

    constexpr property_impl(Get&& getter, Set&& setter) : getter_pointer(getter), setter_pointer(setter) {}

    inline constexpr auto get(const cpp_class* obj) const { return (obj->*getter_pointer)(); }

    inline void set(cpp_class* obj, const typename getter_traits::result& value) const
    {
        (obj->*setter_pointer)(value);
    }

private:
    Get getter_pointer;
    Set setter_pointer;
};

template <typename ClassT, typename T>
constexpr auto nproperty(T ClassT::*&& object_pointer)
{
    return property_impl<T ClassT::*>(std::forward<T ClassT::*&&>(object_pointer));
}

template <typename ClassT, typename T>
constexpr auto nproperty(T (ClassT::*&& getter)() const, void (ClassT::*&& setter)(const T&))
{
    return property_impl<T (ClassT::*)() const, void (ClassT::*)(const T&)>(
        std::forward<T (ClassT::*)() const>(getter), std::forward<void (ClassT::*)(const T&)>(setter));
}

} // namespace ntr