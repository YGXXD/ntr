#include "nreference.h"
#include "nregistrar.h"

namespace ntr
{

template <typename T, typename>
inline nreference::nreference(T&& value) : _type(nullptr), _pdata(nullptr)
{
    _type = ntr::nregistrar::get_type<std::decay_t<T>>();
    _pdata = const_cast<void*>(static_cast<const void*>(&value));
}

template <typename T>
inline T& nreference::ref() const
{
    return *static_cast<T*>(_pdata);
}

template <typename T>
inline const T& nreference::cref() const
{
    return *static_cast<const T*>(_pdata);
}

template <typename T>
inline T&& nreference::rref() const
{
    return std::move(*static_cast<T*>(_pdata));
}

} // namespace ntr