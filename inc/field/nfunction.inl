#pragma once

#include "nfunction.h"
#include "../core/nregistrar.h"

namespace ntr
{

template <typename Ret, typename... Args>
inline nfunction::nfunction(ntype* parent_type, std::string_view name,
                            Ret (*fun)(Args...))
    : nfunction(parent_type, name)
{
    init_function_types<Ret, Args...>();
}

template <typename Ret, typename ClassT, typename... Args>
inline nfunction::nfunction(ntype* parent_type, std::string_view name,
                            Ret (ClassT::*fun)(Args...))
    : nfunction(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not function's class type");
    init_function_types<Ret, Args...>();
}

template <typename Ret, typename ClassT, typename... Args>
inline nfunction::nfunction(ntype* parent_type, std::string_view name,
                            Ret (ClassT::*fun)(Args...) const)
    : nfunction(parent_type, name)
{
    if (parent_type != nregistrar::get_type<ClassT>())
        throw std::invalid_argument("parent type is not function's class type");
    init_function_types<Ret, Args...>();
}

template <typename Ret, typename... Args>
inline void nfunction::init_function_types()
{
    _return_type = nregistrar::get_type<Ret>();
    _argument_types.reserve(sizeof...(Args));
    ((_argument_types.push_back(nregistrar::get_type<Args>())), ...);
}

} // namespace ntr