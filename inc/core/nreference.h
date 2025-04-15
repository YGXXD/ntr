#pragma once

#include "../config.h"

namespace ntr
{

class nreference
{
public:
    template <typename T,
              typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, nreference>>>
    nreference(T&& value);
    nreference(const nreference& other) = default;
    nreference(nreference&& other) = default;
    nreference& operator=(const nreference& other) = default;
    nreference& operator=(nreference&& other) = default;
    ~nreference() = default;

    template <typename T>
    T& ref() const;
    template <typename T>
    const T& cref() const;
    template <typename T>
    T&& rref() const;
    template <typename T>
    T&& any() const;

    inline const class ntype* type() const { return _type; }
    inline void* data() const { return _pdata; }

private:
    const ntype* _type;
    void* _pdata;
};

} // namespace ntr
