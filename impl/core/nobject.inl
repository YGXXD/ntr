#pragma once

#include "../../inc/core/nobject.hpp"
#include "../../inc/core/nregistrar.hpp"

namespace ntr
{

template <typename T, typename>
nobject::nobject(T&& other) : _type(nullptr), _data_ops(nullptr), _small_data()
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
NTR_INLINE T& nobject::as()
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject as type mismatch");
    if constexpr (sizeof(T) <= sizeof(_small_data))
        return *static_cast<T*>(reinterpret_cast<void*>(_small_data));
    else
        return *static_cast<T*>(_large_data);
}

template <typename T>
NTR_INLINE const T& nobject::as() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nobject as type mismatch");
    if constexpr (sizeof(T) <= sizeof(_small_data))
        return *static_cast<const T*>(reinterpret_cast<const void*>(_small_data));
    else
        return *static_cast<const T*>(_large_data);
}

template <typename T>
NTR_INLINE nobject::nobject_data_ops_traits<T>::nobject_data_ops_traits() : ops()
{
    if constexpr (std::is_copy_constructible_v<T>)
    {
        ops.copy = [](void*& self_data, void* const& other_data) -> void
        {
            if constexpr (sizeof(T) <= small_data_size)
                new (&self_data)
                    T(*static_cast<const T*>(reinterpret_cast<const void*>(&other_data)));
            else
                new (self_data) T(*static_cast<const T*>(other_data));
        };
    }
    if constexpr (std::is_move_constructible_v<T>)
    {
        ops.move = [](void*& self_data, void*& other_data) -> void
        {
            if constexpr (sizeof(T) <= small_data_size)
                new (&self_data)
                    T(std::move(*static_cast<T*>(reinterpret_cast<void*>(&other_data))));
            else
                new (self_data) T(std::move(*static_cast<T*>(other_data)));
        };
    }
    if constexpr (std::is_destructible_v<T>)
    {
        ops.release = [](void*& self_data) -> void
        {
            if constexpr (sizeof(T) <= small_data_size)
                static_cast<T*>(reinterpret_cast<void*>(&self_data))->~T();
            else
                delete static_cast<T*>(self_data);
        };
    }
    else
        static_assert(!std::is_same_v<T, T>, "\"T\" has no release operation");
}

nobject nobject::void_ = []() -> nobject
{
    nobject obj {};
    obj._type = nullptr;
    obj._data_ops = &nobject_data_ops_traits<std::byte>::instance().ops;
    return obj;
}();

} // namespace ntr