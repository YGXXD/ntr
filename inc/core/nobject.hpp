//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "nwrapper.hpp"

namespace ntr
{

class NTR_API nobject
{
public:
    enum class eobject : uint8_t
    {
        eobtain,
        eref
    };

    nobject(nobject&& other);
    nobject& operator=(nobject&& other);
    ~nobject();

    bool is_valid() const;
    void* data();
    const void* data() const;

    nobject clone() const;
    nobject steal() const;
    nobject refer() const;
    nwrapper wrapper() const;

    NTR_INLINE const class ntype* type() const { return _type; }
    NTR_INLINE eobject kind() const { return _kind; };
    NTR_INLINE operator nwrapper() { return wrapper(); }

    template <typename T>
    NTR_INLINE T& as();
    template <typename T>
    NTR_INLINE const T& as() const;

private:
    friend class ntype;

    nobject(const ntype* type, eobject kind);
    nobject(const nobject& other) = delete;
    nobject& operator=(const nobject& other) = delete;

    nobject& alloc();
    nobject& init_default();
    nobject& init_copy(const nwrapper& wrapper);
    nobject& init_move(const nwrapper& wrapper);
    nobject& hold_ref(const nwrapper& wrapper);

    const ntype* _type;
    union
    {
        struct
        {
            eobject _kind;
            std::array<std::byte, 7> _status;
        };
        std::array<std::byte, 8> _padding;
    };
    alignas(16) std::array<std::byte, 16> _bytes;
};

} // namespace ntr