#pragma once

#include <tuple>
#include <cstddef>

namespace ntr
{
namespace detail
{

template <typename T>
struct basic_function_traits;

template <typename R, typename... Args>
struct basic_function_traits<R(Args...)>
{
    using result = R;
    using param_pack = std::tuple<Args...>;
    template <size_t Idx>
    using param = typename std::tuple_element<Idx, param_pack>::type;
    static inline constexpr size_t param_count = sizeof...(Args);
};

template <typename T>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<R(Args...)> : basic_function_traits<R(Args...)>
{
    using type = R(Args...);
    using pointer = R (*)(Args...);
    using cpp_class = std::nullptr_t;
    static inline constexpr bool is_menmber = false;
    static inline constexpr bool is_const = false;
};

template <typename ClassT, typename R, typename... Args>
struct function_traits<R (ClassT::*)(Args...)> : basic_function_traits<R(Args...)>
{
    using type = R (ClassT::*)(Args...);
    using pointer = R (ClassT::*)(Args...);
    using cpp_class = ClassT;
    static inline constexpr bool is_menmber = true;
    static inline constexpr bool is_const = false;
};

template <typename ClassT, typename R, typename... Args>
struct function_traits<R (ClassT::*)(Args...) const> : basic_function_traits<R(Args...)>
{
    using type = R (ClassT::*)(Args...) const;
    using pointer = R (ClassT::*)(Args...) const;
    using cpp_class = ClassT;
    static inline constexpr bool is_menmber = true;
    static inline constexpr bool is_const = true;
};

} // namespace detail
} // namespace ntr