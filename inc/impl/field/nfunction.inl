//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "field/nfunction.hpp"
#include "core/nregistrar.hpp"

namespace ntr
{

template <typename Ret, typename... Args, typename OP>
NTR_INLINE nobject nfunction::wrapper_call(OP op,
                                           std::vector<nwrapper>::const_iterator it)
{
    if constexpr (std::is_reference_v<Ret>)
    {
        return nobject::make_ref(op((it++)->unwrap<Args>()...));
    }
    else if constexpr (!std::is_same_v<Ret, void>)
    {
        return nobject::make_obtain(op((it++)->unwrap<Args>()...));
    }
    else
    {
        op((it++)->unwrap<Args>()...);
        return nobject::make_obtain<void>();
    }
}

template <typename Ret, typename... Args>
nfunction::nfunction(const ntype* parent_type, std::string_view name, Ret (*fun)(Args...))
    : nfunction(parent_type, name)
{
    init_function_types<Ret, Args...>();
    _function = [fun](const std::vector<nwrapper>& args) -> nobject
    {
        return wrapper_call<Ret, Args...>(fun, args.begin());
    };
}

template <typename Ret, typename ClassT, typename... Args>
nfunction::nfunction(const ntype* parent_type, std::string_view name,
                     Ret (ClassT::*fun)(Args...))
    : nfunction(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nfunction::nfunction : parent type is not function's class type");
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
nfunction::nfunction(const ntype* parent_type, std::string_view name,
                     Ret (ClassT::*fun)(Args...) const)
    : nfunction(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nfunction::nfunction : parent type is not function's class type");
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
    _return_type = nregistrar::get_type<Ret>();
    _argument_types.reserve(sizeof...(Args));
    ((_argument_types.push_back(nregistrar::get_type<Args>())), ...);
}

} // namespace ntr