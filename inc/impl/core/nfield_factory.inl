//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/nfield_factory.hpp"
#include "../../core/nregistrar.hpp"

namespace ntr
{

template <typename T, typename ClassT>
NTR_INLINE std::unique_ptr<nproperty>
nfield_factory::make_property(const ntype* parent_type, std::string_view name,
                              T(ClassT::* member))
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nfield_factory::make_property : parent type is not property's class type");
    std::function<nobject(const nwrapper&)> getter =
        [member](const nwrapper& instance) -> nobject
    {
        return nregistrar::get_type<T>()->new_reference(instance.cref<ClassT>().*member);
    };
    std::function<void(const nwrapper&, const nwrapper&)> setter =
        [member](const nwrapper& instance, const nwrapper& value)
    {
        instance.ref<ClassT>().*member = value.cref<T>();
    };
    return std::make_unique<nproperty>(parent_type, name, nregistrar::get_type<T>(),
                                       std::move(getter), std::move(setter));
}

template <typename T, typename ClassT>
NTR_INLINE std::unique_ptr<nproperty>
nfield_factory::make_property(const ntype* parent_type, std::string_view name,
                              const T& (ClassT::*getter_fun)() const,
                              void (ClassT::*setter_fun)(const T&))
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nfield_factory::make_property : parent type is not property's class type");
    std::function<nobject(const nwrapper&)> getter =
        [getter_fun](const nwrapper& instance) -> nobject
    {
        return nregistrar::get_type<T>()->new_reference(
            (instance.cref<ClassT>().*getter_fun)());
    };
    std::function<void(const nwrapper&, const nwrapper&)> setter =
        [setter_fun](const nwrapper& instance, const nwrapper& value)
    {
        (instance.ref<ClassT>().*setter_fun)(value.cref<T>());
    };
    return std::make_unique<nproperty>(parent_type, name, nregistrar::get_type<T>(),
                                       std::move(getter), std::move(setter));
}

template <typename Ret, typename... Args>
NTR_INLINE std::unique_ptr<nfunction>
nfield_factory::make_function(const ntype* parent_type, std::string_view name,
                              Ret (*fun)(Args...))
{
    std::function<nobject(const nvector<nwrapper>&)> function =
        [fun](const nvector<nwrapper>& arg_arr) -> nobject
    {
        return function_call<Ret, Args...>(fun, arg_arr.begin());
    };
    return std::make_unique<nfunction>(
        parent_type, name, true, nregistrar::get_type<Ret>(),
        make_function_args<Args...>(), std::move(function));
}

template <typename Ret, typename ClassT, typename... Args>
NTR_INLINE std::unique_ptr<nfunction>
nfield_factory::make_function(const ntype* parent_type, std::string_view name,
                              Ret (ClassT::*fun)(Args...))
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nfield_factory::make_function : parent type is not function's class type");
    std::function<nobject(const nvector<nwrapper>&)> function =
        [fun](const nvector<nwrapper>& arg_arr) -> nobject
    {
        return function_call<Ret, Args...>(
            [instance = arg_arr.begin(), fun](Args... args) -> Ret
        { return (instance->ref<ClassT>().*fun)(std::forward<Args>(args)...); },
            ++arg_arr.begin());
    };
    return std::make_unique<nfunction>(
        parent_type, name, true, nregistrar::get_type<Ret>(),
        make_function_args<ClassT&, Args...>(), std::move(function));
}

template <typename Ret, typename ClassT, typename... Args>
NTR_INLINE std::unique_ptr<nfunction>
nfield_factory::make_function(const ntype* parent_type, std::string_view name,
                              Ret (ClassT::*fun)(Args...) const)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument(
            "nfield_factory::make_function : parent type is not function's class type");
    std::function<nobject(const nvector<nwrapper>&)> function =
        [fun](const nvector<nwrapper>& arg_arr) -> nobject
    {
        return function_call<Ret, Args...>(
            [instance = arg_arr.begin(), fun](Args... args) -> Ret
        { return (instance->cref<ClassT>().*fun)(std::forward<Args>(args)...); },
            ++arg_arr.begin());
    };
    return std::make_unique<nfunction>(
        parent_type, name, true, nregistrar::get_type<Ret>(),
        make_function_args<const ClassT&, Args...>(), std::move(function));
}

template <typename... Args>
NTR_INLINE nvector<const ntype*> nfield_factory::make_function_args()
{
    nvector<const ntype*> args;
    args.reserve(sizeof...(Args));
    ((args.push_back(nregistrar::get_type<Args>())), ...);
    return std::move(args);
}

template <typename Ret, typename... Args, typename OP>
NTR_INLINE nobject nfield_factory::function_call(OP op, nvector<nwrapper>::iterator it)
{
    if constexpr (std::is_reference_v<Ret>)
        return nregistrar::get_type<Ret>()->new_reference(op((it++)->unwrap<Args>()...));
    else if constexpr (!std::is_same_v<Ret, void>)
        return nregistrar::get_type<Ret>()->new_instance_rv(
            op((it++)->unwrap<Args>()...));
    else
    {
        op((it++)->unwrap<Args>()...);
        return nregistrar::get_type<Ret>()->new_instance();
    }
}

} // namespace ntr