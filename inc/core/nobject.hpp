//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "nwrapper.hpp"

#include <cstdint>

namespace ntr
{

class NTR_API nobject
{
public:
    enum class eobject : uint8_t
    {
        eobtain,
        ereference,
    };

    static nobject new_(const ntype* type);
    static nobject copy(const nwrapper& other);
    static nobject move(const nwrapper& other);
    static nobject ref(const nwrapper& ref);

    nobject(nobject&& other);
    nobject& operator=(nobject&& other);
    ~nobject();

    nobject clone() const;
    nobject steal() const;
    nobject hold() const;

    void* data();
    const void* data() const;
    NTR_INLINE bool is_valid() const { return data(); };
    NTR_INLINE bool is_ref() const { return _handle && _handle != _obtain; }
    NTR_INLINE const class ntype* type() const { return _type; }
    NTR_INLINE nwrapper wrapper() const { return nwrapper(_type, data()); };
    NTR_INLINE operator bool() { return is_valid(); }
    NTR_INLINE operator nwrapper() { return wrapper(); }

    template <typename T>
    NTR_INLINE T& as();
    template <typename T>
    NTR_INLINE const T& as() const;

private:
    nobject();
    nobject(const nobject& other) = delete;
    nobject& operator=(const nobject& other) = delete;

    const ntype* _type;
    void* _handle;
    alignas(16) uint64_t _obtain[2];
};

} // namespace ntr