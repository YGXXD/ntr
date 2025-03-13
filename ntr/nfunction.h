#pragma once

#include <string_view>
#include "detail/function_traits.h"

namespace ntr
{

template <typename Impl, typename T>
struct ifunction
{
    inline constexpr auto get_name() const { return static_cast<const Impl*>(this)->get_name_impl(); }

    inline constexpr auto is_const() const { return static_cast<const Impl*>(this)->is_const_impl(); }

    inline constexpr auto is_menmber() const { return static_cast<const Impl*>(this)->is_menmber_impl(); }
};

template <typename Impl, typename ClassT, typename ReturnT, typename... Args>
struct ifunction<Impl, ReturnT (ClassT::*)(Args...)> : ifunction<Impl, void>
{
    inline constexpr ReturnT call(ClassT* instance, Args... args) const
    {
        return static_cast<const Impl*>(this)->call_impl(instance, args...);
    }
};

template <typename Impl, typename ClassT, typename ReturnT, typename... Args>
struct ifunction<Impl, ReturnT (ClassT::*)(Args...) const> : ifunction<Impl, void>
{
    inline constexpr ReturnT call(const ClassT* instance, Args... args) const
    {
        return static_cast<const Impl*>(this)->call_impl(instance, args...);
    }
};

template <typename Impl, typename ReturnT, typename... Args>
struct ifunction<Impl, ReturnT (*)(Args...)> : ifunction<Impl, void>
{
    inline constexpr ReturnT call(Args... args) const { return static_cast<Impl*>(this)->call_impl(args...); }
};

template <typename F, typename = std::enable_if_t<std::is_member_function_pointer_v<F>>>
struct nfunction : ifunction<nfunction<F>, F>
{
    template <typename Impl, typename T>
    friend struct ifunction;

    constexpr nfunction(std::string_view fname, F&& fptr) : name(fname), function_pointer(fptr) {}

private:
    using traits = detail::function_traits<F>;

    constexpr auto get_name_impl() const { return name; }

    constexpr auto is_const_impl() const { return traits::is_const; }

    constexpr auto is_menmber_impl() const { return traits::is_menmber; }

    template <typename... Args>
    inline constexpr auto call_impl(Args&&... args) const
    {
        if constexpr (traits::is_menmber)
            return call_impl(std::forward<Args...>(args)...);
        else
            return function_pointer(std::forward<Args...>(args)...);
    }

    template <typename ClassT, typename... Args>
    inline constexpr auto call_impl(ClassT&& instance, Args&&... args) const
    {
        return (std::forward<ClassT>(instance)->*function_pointer)(std::forward<Args...>(args)...);
    }

private:
    std::string_view name;
    F function_pointer;
};

} // namespace ntr