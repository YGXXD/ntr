#pragma once

#include "../../core/nobject.hpp"
#include "../../core/nwrapper.hpp"
#include "../../core/nregistrar.hpp"

namespace ntr
{

template <typename T>
NTR_INLINE nobject nobject::make_obtain()
{
    return std::move(nobject(nregistrar::get_type<T>(), eobject::eobtain).alloc().init());
}

template <typename T>
NTR_INLINE nobject nobject::make_obtain(T&& value)
{
    nobject obj(nregistrar::get_type<T>(), eobject::eobtain);
    if constexpr (std::is_lvalue_reference_v<T>)
        return std::move(obj.alloc().init_copy(nwrapper(std::forward<T>(value))));
    else
        return std::move(obj.alloc().init_move(nwrapper(std::forward<T>(value))));
}

template <typename T>
NTR_INLINE nobject nobject::make_ref(T&& value)
{
    return std::move(nobject(nregistrar::get_type<T>(), eobject::eref)
                         .hold_ref(nwrapper(std::forward<T>(value))));
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

} // namespace ntr