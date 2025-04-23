#pragma once

#include "../../inc/core/nobject.hpp"
#include "../../inc/core/nwrapper.hpp"
#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE nobject nobject::make()
{
    return std::move(nobject(nregistrar::get_type<T>()).alloc().init());
}

template <typename T>
NTR_INLINE nobject nobject::make(T&& value)
{
    nobject obj(nregistrar::get_type<T>());
    if constexpr (std::is_lvalue_reference_v<T&&>)
        return std::move(obj.alloc().init_copy(&value));
    else if constexpr (std::is_rvalue_reference_v<T&&>)
        return std::move(obj.alloc().init_move(&value));
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

NTR_INLINE nwrapper& nobject::as_wrapper()
{
    return as<nwrapper>();
}

NTR_INLINE const nwrapper& nobject::as_wrapper() const
{
    return as<nwrapper>();
}

} // namespace ntr