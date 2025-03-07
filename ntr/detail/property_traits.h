#pragma once

#include <tuple>
#include <cstddef>

namespace ntr
{
namespace detail
{

template <typename T>
struct property_traits;

template <typename ClassT, typename T>
struct property_traits<T ClassT::*>
{
    using type = T;
    using pointer = T ClassT::*;
    using cpp_class = ClassT;
};

} // namespace detail
} // namespace ntr