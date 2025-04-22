#pragma once

#include "../../inc/core/nobject.hpp"
#include "../../inc/core/nwrapper.hpp"
#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE nobject nobject::make()
{
    return new_init(nregistrar::get_type<T>());
}

template <typename T>
NTR_INLINE nobject nobject::make(T&& value)
{
    if constexpr (std::is_lvalue_reference_v<T&&>)
        return new_clone(nregistrar::get_type<std::decay_t<T>>(), &value);
    else if constexpr (std::is_rvalue_reference_v<T&&>)
        return new_steal(nregistrar::get_type<std::decay_t<T>>(), &value);
    else
        static_assert(!std::is_same_v<T, T>, "nobject::make : unknown type");
}

template <typename T>
NTR_INLINE nobject nobject::make_wrapper(T&& value)
{
    return make(nwrapper(std::forward<T&&>(value)));
}

template <typename T>
NTR_INLINE T& nobject::as()
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject::as : type mismatch");
    return *reinterpret_cast<T*>(data());
}

template <typename T>
NTR_INLINE const T& nobject::as() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject::as : type mismatch");
    return *reinterpret_cast<const T*>(data());
}

template <typename T>
NTR_INLINE T& nobject::as_wrapper_ref() const
{
    return as<nwrapper>().ref<T>();
}

template <typename T>
NTR_INLINE const T& nobject::as_wrapper_cref() const
{
    return as<nwrapper>().cref<T>();
}

} // namespace ntr