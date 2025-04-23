#pragma once

#include "../setup.hpp"

namespace ntr
{

class NTR_API nobject
{
public:
    template <typename T>
    static NTR_INLINE nobject make();
    template <typename T>
    static NTR_INLINE nobject make(T&& value);
    template <typename T>
    static NTR_INLINE nobject make_wrapper(T&& value);

    nobject(const class ntype* type);
    nobject(nobject&& other);
    nobject& operator=(nobject&& other);
    ~nobject();

    template <typename T>
    NTR_INLINE T& as();
    template <typename T>
    NTR_INLINE const T& as() const;
    template <typename T>
    NTR_INLINE T& as_wrapper_ref() const;
    template <typename T>
    NTR_INLINE const T& as_wrapper_cref() const;

    nobject& alloc();
    nobject& init();
    nobject& init_copy(const void* const value);
    nobject& init_move(void* value);

    bool is_heap() const;
    bool is_alloc() const;
    bool is_init() const;

    void* data();
    const void* data() const;
    NTR_INLINE const ntype* type() const { return _type; }

private:
    nobject(const nobject& other) = delete;
    nobject& operator=(const nobject& other) = delete;

    const ntype* _type;
    std::array<std::byte, 8> _status;
    alignas(16) std::array<std::byte, 16> _bytes;
};

} // namespace ntr