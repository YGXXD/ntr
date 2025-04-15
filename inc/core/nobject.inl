#pragma once

#include "nobject.h"
#include "nregistrar.h"

namespace ntr
{

template <typename T, typename>
inline nobject::nobject(T&& other)
    : _type(nullptr), _data_ops(nullptr), _large_data(nullptr)
{
    using U = std::decay_t<T>;
    _type = nregistrar::get_type<U>();
    _data_ops = &nobject_data_ops_traits<U>::instance().ops;
    if constexpr (sizeof(U) <= sizeof(_small_data))
        new (_small_data) U(std::forward<T>(other));
    else
        _large_data = new U(std::forward<T>(other));
}

template <typename T>
inline T& nobject::as()
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject as type mismatch");
    if constexpr (sizeof(T) <= sizeof(_small_data))
        return *reinterpret_cast<T*>(_small_data);
    else
        return *reinterpret_cast<T*>(_large_data);
}

template <typename T>
inline const T& nobject::as() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject as type mismatch");
    if constexpr (sizeof(T) <= sizeof(_small_data))
        return *reinterpret_cast<const T*>(_small_data);
    else
        return *reinterpret_cast<const T*>(_large_data);
}

template <typename T>
inline nobject::nobject_data_ops_traits<T>::nobject_data_ops_traits() : ops()
{
    if constexpr (std::is_copy_constructible_v<T>)
    {
        ops.copy = [](void*& self_data, void* const& other_data) -> void
        {
            if constexpr (sizeof(T) <= small_data_size)
                new (&self_data) T(*reinterpret_cast<const T*>(&other_data));
            else
                self_data = new T(*reinterpret_cast<const T*>(other_data));
        };
    }
    if constexpr (std::is_move_constructible_v<T>)
    {
        ops.move = [](void*& self_data, void*& other_data) -> void
        {
            if constexpr (sizeof(T) <= small_data_size)
                new (&self_data) T(std::move(*reinterpret_cast<T*>(&other_data)));
            else
                self_data = new T(std::move(*reinterpret_cast<T*>(other_data)));
        };
    }
    if constexpr (std::is_destructible_v<T>)
    {
        ops.release = [](void*& self_data) -> void
        {
            if constexpr (sizeof(T) <= small_data_size)
                reinterpret_cast<T*>(&self_data)->~T();
            else
                delete reinterpret_cast<T*>(self_data);
        };
    }
    else
        static_assert(!std::is_same_v<T, T>, "\"T\" has no release operation");
}

} // namespace ntr