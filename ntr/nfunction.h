#pragma once

#include "detail/function_traits.h"

namespace ntr
{

template <typename F, typename = std::enable_if_t<std::is_member_function_pointer_v<F>>>
struct nfunction
{
    using traits = detail::function_traits<F>;
    using cpp_class = typename traits::cpp_class;

    constexpr nfunction(F&& f) : function_pointer(f) {}

    constexpr auto is_const() const { return traits::is_const; }

    constexpr auto is_menmber() const { return traits::is_menmber; }

    template <typename... Args>
    inline constexpr auto operator()(std::conditional_t<traits::is_const, const cpp_class*, cpp_class*> obj,
                                     Args&&... args) const
    {
        return (obj->*function_pointer)(std::forward<Args...>(args)...);
    }

private:
    F function_pointer;
};

} // namespace ntr