#pragma once

#include "nobject.h"
#include "nregistrar.h"
#include <utility>

namespace ntr
{

template <typename T>
inline nobject::nobject(T&& other)
{
    using U = std::decay_t<T>;
    _type = ntr::nregistrar::get_type<U>();
    _ops = nobject_ops_traits<U>::instance().ops;
    if constexpr (sizeof(U) <= sizeof(_data))
    {
        *static_cast<U*>(_data) = other;
    }
    else if constexpr (std::is_lvalue_reference_v<T>)
    {
        _pdata = new U(other);
    }
    else if constexpr (std::is_rvalue_reference_v<T>)
    {
        _pdata = new U(std::move(other));
    }
}

inline nobject::nobject(const nobject& other)
{
    if (_ops->copy)
        _ops->copy(*this, other);
}

inline nobject::nobject(nobject&& other)
{
    if (_ops->move)
        _ops->move(*this, std::move(other));
}

inline nobject& nobject::operator=(const nobject& other)
{
    if (this != &other && _ops->copy)
    {
        _ops->copy(*this, other);
    }
    return *this;
}

inline nobject& nobject::operator=(nobject&& other)
{
    if (this != &other && _ops->move)
    {
        _ops->move(*this, std::move(other));
    }
    return *this;
}

inline nobject::~nobject()
{
    if (_ops->release)
        _ops->release(*this);
}

template <typename T>
inline T& nobject::as()
{
    assert(_type == ntr::nregistrar::get_type<T>());
    if constexpr (sizeof(T) <= sizeof(_data))
    {
        return *reinterpret_cast<T*>(_data);
    }
    else
    {
        return *reinterpret_cast<T*>(_pdata);
    }
}

template <typename T>
inline const T& nobject::as() const
{
    assert(_type == ntr::nregistrar::get_type<T>());
    if constexpr (sizeof(T) <= sizeof(_data))
    {
        return *reinterpret_cast<const T*>(_data);
    }
    else
    {
        return *reinterpret_cast<const T*>(_pdata);
    }
}
} // namespace ntr