#pragma once

#include <tuple>
#include <cstddef>

namespace ntr
{

template <typename T>
struct basic_function_traits;

template <typename R, typename... Args>
struct basic_function_traits<R(Args...)>
{
    using return_type = R;
    using param_types = std::tuple<Args...>;
    template <size_t I>
    using param_type = typename std::tuple_element<I, param_types>::type;
    static inline constexpr size_t param_count = sizeof...(Args);
};

template <typename T>
struct static_function_traits;

template <typename R, typename... Args>
struct static_function_traits<R(Args...)> : basic_function_traits<R(Args...)>
{
    using type = R(Args...);
    using pointer = R (*)(Args...);
    static inline constexpr bool is_menmber = false;
    static inline constexpr bool is_const = false;
};

template <typename R, typename... Args>
struct static_function_traits<R (*)(Args...)> : static_function_traits<R(Args...)>
{
};

template <typename T>
struct member_function_traits;

template <typename ClassT, typename R, typename... Args>
struct member_function_traits<R (ClassT::*)(Args...)> : basic_function_traits<R(Args...)>
{
    using type = R (ClassT::*)(Args...);
    using pointer = R (ClassT::*)(Args...);
    using class_type = ClassT;
    static inline constexpr bool is_const = false;
};

template <typename ClassT, typename R, typename... Args>
struct member_function_traits<R (ClassT::*)(Args...) const> : basic_function_traits<R(Args...)>
{
    using type = R (ClassT::*)(Args...) const;
    using pointer = R (ClassT::*)(Args...) const;
    using class_type = ClassT;
    static inline constexpr bool is_const = true;
};

} // namespace ntr