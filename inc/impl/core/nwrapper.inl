//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "../../core/nwrapper.hpp"
#include "../../core/nregistrar.hpp"

namespace ntr
{

template <typename T, typename>
nwrapper::nwrapper(T&& value) : nwrapper(nregistrar::get_type<T>(), &value)
{
}

template <typename T>
NTR_INLINE T& nwrapper::ref() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nwrapper::ref : type mismatch");
    return *static_cast<T*>(_pdata);
}

template <typename T>
NTR_INLINE const T& nwrapper::cref() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nwrapper::cref : type mismatch");
    return *static_cast<const T*>(_pdata);
}

template <typename T>
NTR_INLINE T&& nwrapper::rref() const
{
    if (_type != nregistrar::get_type<T>())
        throw std::runtime_error("nwrapper::rref : type mismatch");
    return std::move(*static_cast<T*>(_pdata));
}

template <typename T>
NTR_INLINE auto&& nwrapper::unwrap() const
{
    if constexpr (std::is_rvalue_reference_v<T>)
        return rref<std::decay_t<T>>();
    else if constexpr (!std::is_const_v<T>)
        return ref<std::decay_t<T>>();
    else
        return cref<std::decay_t<T>>();
}

template <typename T>
NTR_INLINE nwrapper nwrapper::cast_to() const
{
    return cast_to(nregistrar::get_type<T>());
}

} // namespace ntr