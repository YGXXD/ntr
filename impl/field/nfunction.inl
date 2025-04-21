#pragma once

#include "../../inc/field/nfunction.hpp"
#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename Ret, typename... Args, typename OP>
NTR_INLINE nobject nfunction::wrapper_call(OP op,
                                           std::vector<nwrapper>::const_iterator it)
{
    if constexpr (std::is_lvalue_reference_v<Ret>)
    {
        return nobject::make_wrapper(op((it++)->any<Args>()...));
    }
    else if constexpr (!std::is_same_v<Ret, void>)
    {
        return nobject::make(op((it++)->any<Args>()...));
    }
    else
    {
        op((it++)->any<Args>()...);
        return nobject::make<void>();
    }
}

template <typename Ret, typename... Args>
nfunction::nfunction(ntype* parent_type, std::string_view name, Ret (*fun)(Args...))
    : nfunction(parent_type, name)
{
    init_function_types<Ret, Args...>();
    _function = [fun](const std::vector<nwrapper>& args) -> nobject
    {
        return wrapper_call<Ret, Args...>(fun, args.begin());
    };
}

template <typename Ret, typename ClassT, typename... Args>
nfunction::nfunction(ntype* parent_type, std::string_view name,
                     Ret (ClassT::*fun)(Args...))
    : nfunction(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not function's class type");
    init_function_types<Ret, ClassT&, Args...>();
    _function = [fun](const std::vector<nwrapper>& args) -> nobject
    {
        return wrapper_call<Ret, Args...>(
            [instance = args.begin(), fun](Args... args) -> Ret
        { return (instance->ref<ClassT>().*fun)(args...); },
            args.begin() + 1);
    };
}

template <typename Ret, typename ClassT, typename... Args>
nfunction::nfunction(ntype* parent_type, std::string_view name,
                     Ret (ClassT::*fun)(Args...) const)
    : nfunction(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not function's class type");
    init_function_types<Ret, const ClassT&, Args...>();
    _function = [fun](const std::vector<nwrapper>& args) -> nobject
    {
        return wrapper_call<Ret, Args...>(
            [instance = args.begin(), fun](Args... args) -> Ret
        { return (instance->cref<ClassT>().*fun)(args...); },
            args.begin() + 1);
    };
}

template <typename Ret, typename... Args>
NTR_INLINE void nfunction::init_function_types()
{
    _return_type = nregistrar::get_type<std::decay_t<Ret>>();
    _argument_types.reserve(sizeof...(Args));
    ((_argument_types.push_back(nregistrar::get_type<std::decay_t<Args>>())), ...);
}

} // namespace ntr