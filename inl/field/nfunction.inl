#pragma once

#include "../../inc/field/nfunction.h"
#include "../../inc/core/nregistrar.h"

namespace ntr
{

template <typename Ret, typename... Args>
nfunction::nfunction(ntype* parent_type, std::string_view name, Ret (*fun)(Args...))
    : nfunction(parent_type, name)
{
    init_function_types<Ret, Args...>();
    _function = [fun](const std::vector<nreference>& args) -> nobject
    {
        std::vector<nreference>::const_iterator it = args.begin();
        if constexpr (std::is_lvalue_reference_v<Ret>)
        {
            return nobject(nreference((*fun)(*(it++)->any<Args>()...)));
        }
        else if constexpr (!std::is_same_v<Ret, void>)
        {
            return nobject((*fun)(*(it++)->any<Args>()...));
        }
        else
        {
            (*fun)((it++)->any<Args>()...);
            return nobject(nullptr);
        }
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
    _function = [fun](const std::vector<nreference>& args) -> nobject
    {
        std::vector<nreference>::const_iterator it = args.begin() + 1;
        if constexpr (std::is_lvalue_reference_v<Ret>)
        {
            return nobject(
                nreference((args.begin()->ref<ClassT>().*fun)((it++)->any<Args>()...)));
        }
        if constexpr (!std::is_same_v<Ret, void>)
        {
            return nobject((args.begin()->ref<ClassT>().*fun)((it++)->any<Args>()...));
        }
        else
        {
            (args.begin()->ref<ClassT>().*fun)((it++)->any<Args>()...);
            return nobject(nullptr);
        }
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
    _function = [fun](const std::vector<nreference>& args) -> nobject
    {
        std::vector<nreference>::const_iterator it = args.begin() + 1;
        if constexpr (std::is_lvalue_reference_v<Ret>)
        {
            return nobject(
                nreference((args.begin()->cref<ClassT>().*fun)((it++)->any<Args>()...)));
        }
        if constexpr (!std::is_same_v<Ret, void>)
        {
            return nobject((args.begin()->cref<ClassT>().*fun)((it++)->any<Args>()...));
        }
        else
        {
            (args.begin()->cref<ClassT>().*fun)((it++)->any<Args>()...);
            return nobject(nullptr);
        }
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