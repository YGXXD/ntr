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

    static nobject new_(const class ntype* type);
    static nobject new_copy_(const ntype* type, const void* const data);
    static nobject new_steal_(const ntype* type, void* data);

    nobject(nobject&& other);
    nobject& operator=(nobject&& other);
    ~nobject();

    template <typename T>
    NTR_INLINE T& as();
    template <typename T>
    NTR_INLINE const T& as() const;

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