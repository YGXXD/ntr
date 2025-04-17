#pragma once

#include "../setup.hpp"

#define NTR_OBJECT_SMALL_SIZE 16

namespace ntr
{

class NTR_API nobject
{
public:
    template <typename T,
              typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, nobject>>>
    nobject(T&& other);
    nobject(const nobject& other);
    nobject(nobject&& other);
    nobject& operator=(const nobject& other);
    nobject& operator=(nobject&& other);
    ~nobject();

    template <typename T>
    NTR_INLINE T& as();
    template <typename T>
    NTR_INLINE const T& as() const;

    NTR_INLINE const class ntype* type() const { return _type; }
    NTR_INLINE void* data() const { return _large_data; }

    static nobject void_;

private:
    nobject() = default;

    void copy(const nobject& other);
    void move(nobject&& other);
    void destruct();

    const ntype* _type;
    union
    {
        std::byte _small_data[NTR_OBJECT_SMALL_SIZE];
        std::byte* _large_data;
    };
};

} // namespace ntr