#pragma once

#include <string_view>
#include "detail/function_traits.h"

namespace ntr
{

template <typename F, typename = std::enable_if_t<std::is_member_function_pointer_v<F>>>
struct nfunction
{
    using traits = detail::function_traits<F>;
    using cpp_class = typename traits::cpp_class;
    using instance_pointer = std::conditional_t<traits::is_const, const cpp_class*, cpp_class*>;

    constexpr nfunction(std::string_view fname, F&& fptr) : name(fname), function_pointer(fptr) {}

    constexpr auto get_name() const { return name; }

    constexpr auto is_const() const { return traits::is_const; }

    constexpr auto is_menmber() const { return traits::is_menmber; }

    template <typename... Args>
    inline constexpr auto operator()(instance_pointer instance, Args&&... args) const
    {
        return (instance->*function_pointer)(std::forward<Args...>(args)...);
    }

private:
    F function_pointer;
    std::string_view name;
};

} // namespace ntr