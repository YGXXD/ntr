#pragma once

namespace ntr
{

template <typename T>
class singleton
{
public:
    static inline T& instance()
    {
        static T _instance {};
        return _instance;
    }
};

} // namespace ntr