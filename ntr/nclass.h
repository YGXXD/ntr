#pragma once

#include <array>
#include <tuple>
#include <string_view>

namespace ntr
{

template <typename T>
struct nclass;

template <typename T>
inline constexpr size_t function_id(std::string_view function_name)
{
    int it = 0;
    int id = -1;
    std::apply([&](auto... function) { (((function_name == function.get_name() && id < 0) && (id = it), ++it), ...); },
               nclass<T>::functions);
    return static_cast<size_t>(id & 0x3fffffff);
}

template <typename T>
inline constexpr size_t property_id(std::string_view property_name)
{
    int it = 0;
    int id = -1;
    std::apply([&](auto... property) { (((property_name == property.get_name() && id < 0) && (id = it), ++it), ...); },
               nclass<T>::properties);
    return static_cast<size_t>(id & 0x3fffffff) | (1 << 30);
}

} // namespace ntr