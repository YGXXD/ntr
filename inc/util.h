#pragma once

#include <type_traits>

namespace ntr
{

template <typename T>
struct always_false : std::false_type
{
};

template <typename T>
struct singleton
{
    static inline T& instance()
    {
        static T _instance;
        return _instance;
    }
};

} // namespace ntr