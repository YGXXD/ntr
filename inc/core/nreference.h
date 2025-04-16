#pragma once

#include "../setup.h"

namespace ntr
{

class NTR_API nreference
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
    NTR_INLINE T& ref() const;
    template <typename T>
    NTR_INLINE const T& cref() const;
    template <typename T>
    NTR_INLINE T&& rref() const;
    template <typename T>
    NTR_INLINE auto&& any() const;

    NTR_INLINE const class ntype* type() const { return _type; }
    NTR_INLINE void* data() const { return _pdata; }

private:
    const ntype* _type;
    void* _pdata;
};

} // namespace ntr
