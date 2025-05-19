//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"

namespace ntr
{

class NTR_API nwrapper
{
public:
    template <typename T,
              typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, nwrapper>>>
    nwrapper(T&& value);
    nwrapper(const class ntype* type, const void* data);
    nwrapper(const nwrapper& other) = default;
    nwrapper(nwrapper&& other) = default;
    nwrapper& operator=(const nwrapper& other) = default;
    nwrapper& operator=(nwrapper&& other) = default;
    ~nwrapper() = default;

    template <typename T>
    NTR_INLINE T& ref() const;
    template <typename T>
    NTR_INLINE const T& cref() const;
    template <typename T>
    NTR_INLINE T&& rref() const;
    template <typename T>
    NTR_INLINE auto&& unwrap() const;

    NTR_INLINE const ntype* type() const { return _type; }
    NTR_INLINE void* data() const { return _pdata; }

private:
    const ntype* _type;
    void* _pdata;
};

} // namespace ntr
