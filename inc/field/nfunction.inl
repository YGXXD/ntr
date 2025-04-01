#pragma once

#include "nfunction.h"
#include "../nephren.h"

namespace ntr
{

// construct
inline nfunction::nfunction(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
}

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
    assert(parent_type == nephren::get_type<ClassT>());
    init_function_types<Ret, Args...>();
}

template <typename Ret, typename ClassT, typename... Args>
inline nfunction::nfunction(ntype* parent_type, std::string_view name,
                            Ret (ClassT::*fun)(Args...) const)
    : nfunction(parent_type, name)
{
    assert(parent_type == nephren::get_type<ClassT>());
    init_function_types<Ret, Args...>();
}

// logic
template <typename Ret, typename... Args>
inline void nfunction::init_function_types()
{
    if constexpr (!std::is_same_v<Ret, void>)
    {
        _return_type = nephren::get_type<std::decay_t<Ret>>();
        assert(_return_type != nullptr);
    }
    _argument_types.reserve(sizeof...(Args));
    ((_argument_types.push_back(nephren::get_type<std::decay_t<Args>>()),
      assert(_argument_types.back() != nullptr)),
     ...);
}

// get
inline const ntype* nfunction::return_type() const
{
    return _return_type;
}

inline const std::vector<const ntype*>& nfunction::argument_types() const
{
    return _argument_types;
}

} // namespace ntr