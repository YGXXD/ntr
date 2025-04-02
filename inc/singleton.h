#pragma once

namespace ntr
{

template <typename T>
struct singleton
{
    static inline T& instance()
    {
        static T _instance {};
        return _instance;
    }
};

} // namespace ntr