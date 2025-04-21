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

    static nobject new_init(const class ntype* type);
    static nobject new_clone(const class ntype* type, const void* const data);
    static nobject new_steal(const class ntype* type, void* data);

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

    bool is_heap() const;
    bool is_valid() const;
    std::byte* data();
    const std::byte* data() const;

    NTR_INLINE const ntype* type() const { return _type; }

private:
    nobject() = default;
    nobject(const ntype* type);
    nobject(const nobject& other) = delete;
    nobject& operator=(const nobject& other) = delete;

    const ntype* _type;
    union
    {
        std::array<std::byte, 24> _small_data;
        std::byte* _large_data;
    };
};

} // namespace ntr