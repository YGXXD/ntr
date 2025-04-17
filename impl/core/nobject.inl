#pragma once

#include "../../inc/core/nobject.hpp"
#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T, typename>
nobject::nobject(T&& other) : _type(nullptr), _small_data()
{
    using U = std::decay_t<T>;
    _type = nregistrar::get_type<U>();
    if constexpr (sizeof(U) <= sizeof(_small_data))
        new (_small_data) U(std::forward<T>(other));
    else
        _large_data = new U(std::forward<T>(other));
}

template <typename T>
NTR_INLINE T& nobject::as()
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject as type mismatch");
    if constexpr (sizeof(T) <= sizeof(_small_data))
        return *reinterpret_cast<T*>(_small_data);
    else
        return *reinterpret_cast<T*>(_large_data);
}

template <typename T>
NTR_INLINE const T& nobject::as() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject as type mismatch");
    if constexpr (sizeof(T) <= sizeof(_small_data))
        return *reinterpret_cast<const T*>(_small_data);
    else
        return *reinterpret_cast<const T*>(_large_data);
}

} // namespace ntr