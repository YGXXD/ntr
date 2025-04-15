#include "nreference.h"
#include "nregistrar.h"

namespace ntr
{

template <typename T, typename>
inline nreference::nreference(T&& value) : _type(nullptr), _pdata(nullptr)
{
    _type = nregistrar::get_type<std::decay_t<T>>();
    _pdata = const_cast<void*>(reinterpret_cast<const void*>(&value));
}

template <typename T>
inline T& nreference::ref() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nreference ref type mismatch");
    return *reinterpret_cast<T*>(_pdata);
}

template <typename T>
inline const T& nreference::cref() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nreference cref type mismatch");
    return *reinterpret_cast<const T*>(_pdata);
}

template <typename T>
inline T&& nreference::rref() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nreference rref type mismatch");
    return std::move(*reinterpret_cast<T*>(_pdata));
}

template <typename T>
inline auto&& nreference::any() const
{
    if constexpr (std::is_rvalue_reference_v<T>)
        return rref<std::decay_t<T>>();
    else if constexpr (std::is_lvalue_reference_v<T> && !std::is_const_v<T>)
        return ref<std::decay_t<T>>();
    else
        return cref<std::decay_t<T>>();
}

} // namespace ntr