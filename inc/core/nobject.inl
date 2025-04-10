#pragma once

#include "nobject.h"
#include "nregistrar.h"
#include <utility>

namespace ntr
{

template <typename T, typename>
inline nobject::nobject(T&& other) : _type(nullptr), _data_ops(nullptr), _large_data(nullptr)
{
    using U = std::decay_t<T>;
    _type = ntr::nregistrar::get_type<U>();
    _data_ops = &nobject_data_ops_traits<U>::instance().ops;
    if constexpr (sizeof(U) <= sizeof(_small_data))
        new (_small_data) U(std::forward<T>(other));
    else
        _large_data = new U(std::forward<T>(other));
}

inline nobject::nobject(const nobject& other) : _type(other._type), _data_ops(other._data_ops)
{
    if (_data_ops && _data_ops->copy)
        _data_ops->copy(_large_data, other._large_data);
}

inline nobject::nobject(nobject&& other) : _type(other._type), _data_ops(other._data_ops)
{
    if (_data_ops && _data_ops->move)
        _data_ops->move(_large_data, other._large_data);
}

inline nobject& nobject::operator=(const nobject& other)
{
    if (this != &other)
    {
        _type = other._type;
        _data_ops = other._data_ops;
        _data_ops->copy(_large_data, other._large_data);
    }
    return *this;
}

inline nobject& nobject::operator=(nobject&& other)
{
    if (this != &other)
    {
        _type = other._type;
        _data_ops = other._data_ops;
        _data_ops->move(_large_data, other._large_data);
    }
    return *this;
}

inline nobject::~nobject()
{
    if (_data_ops && _data_ops->release)
        _data_ops->release(_large_data);
}

template <typename T>
inline T& nobject::as()
{
    if (_type != ntr::nregistrar::get_type<T>())
    {
        throw std::runtime_error("nobject as type mismatch");
    }
    if constexpr (sizeof(T) <= sizeof(_small_data))
    {
        return *reinterpret_cast<T*>(_small_data);
    }
    else
    {
        return *reinterpret_cast<T*>(_large_data);
    }
}

template <typename T>
inline const T& nobject::as() const
{
    if (_type != ntr::nregistrar::get_type<T>())
    {
        throw std::runtime_error("nobject as type mismatch");
    }
    if constexpr (sizeof(T) <= sizeof(_small_data))
    {
        return *reinterpret_cast<const T*>(_small_data);
    }
    else
    {
        return *reinterpret_cast<const T*>(_large_data);
    }
}
} // namespace ntr